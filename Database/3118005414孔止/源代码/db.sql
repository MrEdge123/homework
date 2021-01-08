CREATE DATABASE  IF NOT EXISTS `education_system` /*!40100 DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci */ /*!80016 DEFAULT ENCRYPTION='N' */;
USE `education_system`;
-- MySQL dump 10.13  Distrib 8.0.22, for Win64 (x86_64)
--
-- Host: localhost    Database: education_system
-- ------------------------------------------------------
-- Server version	8.0.22

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `course`
--

DROP TABLE IF EXISTS `course`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `course` (
  `no` char(10) NOT NULL,
  `name` char(10) DEFAULT NULL,
  `hour` float DEFAULT NULL,
  `credit` float DEFAULT NULL,
  PRIMARY KEY (`no`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `course`
--

LOCK TABLES `course` WRITE;
/*!40000 ALTER TABLE `course` DISABLE KEYS */;
INSERT INTO `course` VALUES ('001001','C语言程序设计',48,4),('001002','计算机导论',16,2),('001003','数字逻辑EDA',36,3),('001004','数据结构',48,5),('001005','计算机网络',48,5),('001006','计算机组成原理',48,5),('004001','高等数学',88,5.5);
/*!40000 ALTER TABLE `course` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `sdept`
--

DROP TABLE IF EXISTS `sdept`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `sdept` (
  `no` char(10) NOT NULL,
  `name` char(10) DEFAULT NULL,
  `introduction` text,
  PRIMARY KEY (`no`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `sdept`
--

LOCK TABLES `sdept` WRITE;
/*!40000 ALTER TABLE `sdept` DISABLE KEYS */;
INSERT INTO `sdept` VALUES ('001','计算机学院','计算机学院的简介'),('002','自动化学院','自动化学院'),('003','材料与能源学院','材料与能源学院的简介'),('004','数学学院','数学学院'),('005','信息工程学院','信息工程学院');
/*!40000 ALTER TABLE `sdept` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `student`
--

DROP TABLE IF EXISTS `student`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `student` (
  `no` char(10) NOT NULL,
  `name` char(10) DEFAULT NULL,
  `sex` char(5) DEFAULT NULL,
  `birth` date DEFAULT NULL,
  `ad_score` float DEFAULT NULL,
  `sdept_no` char(10) DEFAULT NULL,
  PRIMARY KEY (`no`),
  KEY `sdept_no` (`sdept_no`),
  CONSTRAINT `student_ibfk_1` FOREIGN KEY (`no`) REFERENCES `user` (`no`),
  CONSTRAINT `student_ibfk_2` FOREIGN KEY (`sdept_no`) REFERENCES `sdept` (`no`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `student`
--

LOCK TABLES `student` WRITE;
/*!40000 ALTER TABLE `student` DISABLE KEYS */;
INSERT INTO `student` VALUES ('20210001','学生1','男','2001-04-05',550,'001'),('20210002','学生2','女','2000-01-01',560,'001'),('20210003','学生3','男',NULL,570,'001'),('20210004','学生4','女',NULL,580,'001'),('20210005','学生5','男',NULL,590,'001'),('20210006','学生6','男','2001-03-02',555,'002');
/*!40000 ALTER TABLE `student` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `student_course`
--

DROP TABLE IF EXISTS `student_course`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `student_course` (
  `student_no` char(10) NOT NULL,
  `tc_no` char(10) NOT NULL,
  `usual_score` float DEFAULT NULL,
  `exam_score` float DEFAULT NULL,
  `score` float DEFAULT NULL,
  PRIMARY KEY (`student_no`,`tc_no`),
  KEY `tc_no` (`tc_no`),
  CONSTRAINT `student_course_ibfk_1` FOREIGN KEY (`student_no`) REFERENCES `student` (`no`),
  CONSTRAINT `student_course_ibfk_2` FOREIGN KEY (`tc_no`) REFERENCES `teacher_course` (`no`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `student_course`
--

LOCK TABLES `student_course` WRITE;
/*!40000 ALTER TABLE `student_course` DISABLE KEYS */;
INSERT INTO `student_course` VALUES ('20210001','0210010010',NULL,NULL,NULL),('20210001','0210010020',NULL,NULL,NULL),('20210001','0210010030',NULL,NULL,NULL),('20210001','0210010040',NULL,NULL,NULL);
/*!40000 ALTER TABLE `student_course` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `teacher`
--

DROP TABLE IF EXISTS `teacher`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `teacher` (
  `no` char(10) NOT NULL,
  `name` char(10) DEFAULT NULL,
  `sex` char(5) DEFAULT NULL,
  `birth` date DEFAULT NULL,
  `sdept_no` char(10) DEFAULT NULL,
  `job_title` char(10) DEFAULT NULL,
  `direction` char(20) DEFAULT NULL,
  PRIMARY KEY (`no`),
  KEY `sdept_no` (`sdept_no`),
  CONSTRAINT `teacher_ibfk_1` FOREIGN KEY (`no`) REFERENCES `user` (`no`),
  CONSTRAINT `teacher_ibfk_2` FOREIGN KEY (`sdept_no`) REFERENCES `sdept` (`no`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `teacher`
--

LOCK TABLES `teacher` WRITE;
/*!40000 ALTER TABLE `teacher` DISABLE KEYS */;
INSERT INTO `teacher` VALUES ('20211001','教师1','男',NULL,'001',NULL,NULL),('20211002','教师2','女',NULL,'001',NULL,NULL),('20211003','教师3','男',NULL,'001',NULL,NULL),('20211004','教师4','女',NULL,'001',NULL,NULL),('20211005','教师5','男',NULL,'004',NULL,NULL);
/*!40000 ALTER TABLE `teacher` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `teacher_course`
--

DROP TABLE IF EXISTS `teacher_course`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `teacher_course` (
  `no` char(10) NOT NULL,
  `course_no` char(10) DEFAULT NULL,
  `teacher_no` char(10) DEFAULT NULL,
  `semester` char(20) DEFAULT NULL,
  `class_time` char(20) DEFAULT NULL,
  `class_location` char(20) DEFAULT NULL,
  `exam_time` datetime DEFAULT NULL,
  PRIMARY KEY (`no`),
  KEY `course_no` (`course_no`),
  KEY `teacher_no` (`teacher_no`),
  CONSTRAINT `teacher_course_ibfk_1` FOREIGN KEY (`course_no`) REFERENCES `course` (`no`),
  CONSTRAINT `teacher_course_ibfk_2` FOREIGN KEY (`teacher_no`) REFERENCES `teacher` (`no`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `teacher_course`
--

LOCK TABLES `teacher_course` WRITE;
/*!40000 ALTER TABLE `teacher_course` DISABLE KEYS */;
INSERT INTO `teacher_course` VALUES ('0210010010','001001','20211001','2021年上','周三3,4节','教1-205',NULL),('0210010020','001002','20211002','2021年上','周二3,4节','教2-304',NULL),('0210010030','001003','20211002','2021年上','周一6,7节','教4-405',NULL),('0210010040','001004','20211003','2021年上','周四6,7节','教5-310',NULL),('0210010050','001005','20211004','2021年上','周五1,2节','教3-210',NULL),('0210040010','004001','20211005','2021年上','周五6,7节','教3-105',NULL);
/*!40000 ALTER TABLE `teacher_course` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `user`
--

DROP TABLE IF EXISTS `user`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `user` (
  `no` char(10) NOT NULL,
  `password` char(20) DEFAULT NULL,
  `identity` char(10) DEFAULT NULL,
  PRIMARY KEY (`no`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `user`
--

LOCK TABLES `user` WRITE;
/*!40000 ALTER TABLE `user` DISABLE KEYS */;
INSERT INTO `user` VALUES ('00000000','admin','管理员'),('20210001','123456','学生'),('20210002','123456','学生'),('20210003','123456','学生'),('20210004','123456','学生'),('20210005','123456','学生'),('20210006','123456','学生'),('20211001','123456','老师'),('20211002','123456','老师'),('20211003','123456','老师'),('20211004','123456','老师'),('20211005','123456','老师');
/*!40000 ALTER TABLE `user` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2021-01-06 23:11:27
