using System.IO;
using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
using UnityEngine;

public class PlayerController : MonoBehaviour
{
    private Rigidbody rgbody;      //小球属性

    private Text score_text;       //显示分数

    private Text time_text;        //显示时间

    private float used_time;       //已用时间

    private GameObject end_text;   //结束文字

    private GameObject display_rank; //显示排行榜面板

    private GameObject[] rank_time;    //排名-时间

    private ArrayList time_list;

    private GameObject begin_text; //开始数字

    private int force;       //力的大小

    private int score;       //已得分数

    private bool jump_lock;  //跳跃锁

    private AudioSource audio_source;    //背景音乐

    private AudioClip pick_up_audio;     //拾物音效

    private float count_down;

    private bool is_begin;

    void Start()
    {
        rgbody = GetComponent<Rigidbody>();   //获得小球控制权

        force = 10;     //10倍力度

        //分数显示
        score = 0;
        score_text = GameObject.Find("Canvas/Score Text").GetComponent<Text>();
        score_text.text = string.Format("当前得分为: {0}", score);

        //时间显示
        used_time = 0f;
        time_text = GameObject.Find("Canvas/Time Text").GetComponent<Text>();
        time_text.text = string.Format("已用时间: {0:00.00}", used_time);

        //游戏结束显示
        end_text = GameObject.Find("Canvas/End Text");
        end_text.SetActive(false);

        //排名-时间
        rank_time = new GameObject[11];

        //排行榜
        display_rank = GameObject.Find("Canvas/Rank Panel");
        InitRank();
        display_rank.SetActive(false);

        //开始倒计时
        begin_text = GameObject.Find("Canvas/Begin Text");

        //初始化跳跃锁
        jump_lock = false;

        //设置拾物音乐
        audio_source = GetComponent<AudioSource>();           
        pick_up_audio = Resources.Load<AudioClip>("Audio/Pick Up3");

        //倒计时和开始游戏
        count_down = 3f;
        is_begin = false;
    }

    void FixedUpdate()
    {
        //游戏退出
        if (Input.GetKey(KeyCode.Escape))
        {
            Application.Quit();
        }

        if (is_begin == false) return;

        bool ok = false;

        //控制小球方向
        if(Input.GetKey(KeyCode.UpArrow) || Input.GetKey(KeyCode.W))
        {
            rgbody.AddForce(Vector3.forward * force);
            ok = true;
        }
        if(Input.GetKey(KeyCode.DownArrow) || Input.GetKey(KeyCode.S))
        {
            rgbody.AddForce(Vector3.back * force);
            ok = true;
        }
        if(Input.GetKey(KeyCode.LeftArrow) || Input.GetKey(KeyCode.A))
        {
            rgbody.AddForce(Vector3.left * force);
            ok = true;
        }
        if(Input.GetKey(KeyCode.RightArrow) || Input.GetKey(KeyCode.D))
        {
            rgbody.AddForce(Vector3.right * force);
            ok = true;
        }
        if (Input.GetKey(KeyCode.Space) && jump_lock == false)
        {
            rgbody.AddForce(Vector3.up * force * 20);
            ok = true;
            jump_lock = true;   //跳跃起来时设置跳跃锁
        }

        //没有控制小球时停下来
        if (ok == false)
        {
            Vector3 vec = rgbody.velocity;
            rgbody.AddForce(new Vector3(-vec.x, 0, -vec.z));
        }

        //重置游戏
        if(Input.GetKey(KeyCode.R))
        {
            SceneManager.LoadScene("Game Scene");
        }
    }

    void Update()
    {
        //显示倒计时
        if(count_down > 0)
        {
            count_down -= Time.deltaTime;
            begin_text.GetComponent<Text>().text = string.Format("{0}", (int)count_down + 1);
        }
        else if(is_begin == false)
        {
            is_begin = true;
            begin_text.SetActive(false);

        }
        
        //显示已用时间
        if(is_begin && score != 12)
        {
            used_time += Time.deltaTime;
            time_text.text = string.Format("已用时间: {0:00.00}", used_time);
        }

        //排行榜
        if (Input.GetKeyDown(KeyCode.Q))
        {
            if (display_rank.activeSelf)
            {
                display_rank.SetActive(false);
            }
            else
            {
                DisplayRank();
            }
        }
    }

    private void OnTriggerEnter(Collider other)
    {
        //拾物后的操作
        if(other.gameObject.CompareTag("Pick Up"))
        {
            other.gameObject.SetActive(false);   //使被拾物消失
            score++;
            //Debug.Log(string.Format("当前分数为:{0}", score));
            score_text.text = string.Format("当前得分为: {0}", score);

            //播放拾物音效
            audio_source.clip = pick_up_audio;
            audio_source.Play();

            //显示游戏结束
            if (score == 12)
            {
                //end_text.SetActive(true);

                //写入当前时间
                WriteRankTime();

                //显示排名
                DisplayRank();
            }
        }
    }

    private void OnCollisionEnter(Collision collision)
    {
        //回到地面, 解除跳跃锁
        if(collision.gameObject.CompareTag("Ground"))
        {
            jump_lock = false;
        }
        if (collision.gameObject.CompareTag("Wall"))
        {
            rgbody.AddForce(-rgbody.transform.position * 100);
        }
    }

    private void WriteRankTime()
    {
        string str = string.Format("{0:00.00}", used_time);
        using (StreamWriter sw = new StreamWriter("rank_time.txt", true))
        {
            sw.WriteLine(str);
        }
    }

    private void ReadRankTime()
    {
        time_list = new ArrayList();
        using (StreamReader sr = new StreamReader("rank_time.txt"))
        {
            string line = sr.ReadLine();
            while(line != null)
            {
                time_list.Add(float.Parse(line));
                line = sr.ReadLine();
            }

            time_list.Sort();
        }
    }

    private void InitRank()
    {
        rank_time[0] = GameObject.Find("Canvas/Rank Panel/Scroll View/Viewport/Content/Rank Time");

        GameObject par = GameObject.Find("Canvas/Rank Panel/Scroll View/Viewport/Content");

        //初始化排名-时间
        for (int i = 1; i <= 10; i++)
        {
            rank_time[i] = Instantiate(rank_time[0], par.transform);
            Text rank_text = rank_time[i].transform.Find("Rank").GetComponent<Text>();
            Text time_text = rank_time[i].transform.Find("Time").GetComponent<Text>();
            rank_text.text = string.Format("{0}", i);
            time_text.text = "";
        }
    }

    private void DisplayRank()
    {
        display_rank.SetActive(true);

        //读取当前时间
        ReadRankTime();

        for (int i = 1; i <= 10; i++)
        {
            Text time_text = rank_time[i].transform.Find("Time").GetComponent<Text>();
            if ((i - 1) < time_list.Count)
            {
                time_text.text = string.Format("{0:00.00}", time_list[i - 1]);
            }
        }
    }
}
