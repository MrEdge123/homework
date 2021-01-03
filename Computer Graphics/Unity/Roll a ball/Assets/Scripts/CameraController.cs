using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraController : MonoBehaviour
{
    public GameObject player;

    private Vector3 offset;   //相机和小球的相对偏移量

    // Start is called before the first frame update
    void Start()
    {
        //计算相机和小球的相对偏移量
        offset = transform.position - player.transform.position;
    }

    // Update is called once per frame
    void LateUpdate()
    {
        //保持相机和小球相对位置不变
        transform.position = player.transform.position + offset;
    }
}
