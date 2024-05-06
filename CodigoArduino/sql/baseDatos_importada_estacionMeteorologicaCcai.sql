-- MySQL dump 10.13  Distrib 8.0.26, for Win64 (x86_64)
--
-- Host: localhost    Database: estacionmeteorologico
-- ------------------------------------------------------
-- Server version	5.7.35-log

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
-- Temporary view structure for view `get_databymonth`
--

DROP TABLE IF EXISTS `get_databymonth`;
/*!50001 DROP VIEW IF EXISTS `get_databymonth`*/;
SET @saved_cs_client     = @@character_set_client;
/*!50503 SET character_set_client = utf8mb4 */;
/*!50001 CREATE VIEW `get_databymonth` AS SELECT 
 1 AS `id_weather`,
 1 AS `temperature`,
 1 AS `pressure`,
 1 AS `altitude`,
 1 AS `air_quality`,
 1 AS `date_time`*/;
SET character_set_client = @saved_cs_client;

--
-- Temporary view structure for view `get_realtimedata`
--

DROP TABLE IF EXISTS `get_realtimedata`;
/*!50001 DROP VIEW IF EXISTS `get_realtimedata`*/;
SET @saved_cs_client     = @@character_set_client;
/*!50503 SET character_set_client = utf8mb4 */;
/*!50001 CREATE VIEW `get_realtimedata` AS SELECT 
 1 AS `id_weather`,
 1 AS `temperature`,
 1 AS `pressure`,
 1 AS `altitude`,
 1 AS `air_quality`,
 1 AS `date_time`*/;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `weather_measurements`
--

DROP TABLE IF EXISTS `weather_measurements`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `weather_measurements` (
  `id_weather` int(11) NOT NULL AUTO_INCREMENT,
  `temperature` decimal(10,2) DEFAULT NULL,
  `pressure` decimal(10,2) DEFAULT NULL,
  `altitude` decimal(10,2) DEFAULT NULL,
  `air_quality` decimal(10,2) DEFAULT NULL,
  `date_time` datetime DEFAULT NULL,
  PRIMARY KEY (`id_weather`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `weather_measurements`
--

LOCK TABLES `weather_measurements` WRITE;
/*!40000 ALTER TABLE `weather_measurements` DISABLE KEYS */;
INSERT INTO `weather_measurements` VALUES (1,20.00,20.00,20.00,20.00,'2023-05-28 17:18:58'),(2,21.00,20.00,20.00,20.00,'2023-05-28 17:19:36'),(3,40.00,40.00,40.00,40.00,'2023-05-28 17:34:39'),(4,40.00,40.00,40.00,40.00,'2023-05-28 17:40:47'),(5,40.00,40.00,40.00,40.00,'2023-05-28 17:41:36');
/*!40000 ALTER TABLE `weather_measurements` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Final view structure for view `get_databymonth`
--

/*!50001 DROP VIEW IF EXISTS `get_databymonth`*/;
/*!50001 SET @saved_cs_client          = @@character_set_client */;
/*!50001 SET @saved_cs_results         = @@character_set_results */;
/*!50001 SET @saved_col_connection     = @@collation_connection */;
/*!50001 SET character_set_client      = utf8mb4 */;
/*!50001 SET character_set_results     = utf8mb4 */;
/*!50001 SET collation_connection      = utf8mb4_general_ci */;
/*!50001 CREATE ALGORITHM=UNDEFINED */
/*!50013 DEFINER=`root`@`localhost` SQL SECURITY DEFINER */
/*!50001 VIEW `get_databymonth` AS select `weather_measurements`.`id_weather` AS `id_weather`,`weather_measurements`.`temperature` AS `temperature`,`weather_measurements`.`pressure` AS `pressure`,`weather_measurements`.`altitude` AS `altitude`,`weather_measurements`.`air_quality` AS `air_quality`,`weather_measurements`.`date_time` AS `date_time` from `weather_measurements` where (month(`weather_measurements`.`date_time`) = month(now())) */;
/*!50001 SET character_set_client      = @saved_cs_client */;
/*!50001 SET character_set_results     = @saved_cs_results */;
/*!50001 SET collation_connection      = @saved_col_connection */;

--
-- Final view structure for view `get_realtimedata`
--

/*!50001 DROP VIEW IF EXISTS `get_realtimedata`*/;
/*!50001 SET @saved_cs_client          = @@character_set_client */;
/*!50001 SET @saved_cs_results         = @@character_set_results */;
/*!50001 SET @saved_col_connection     = @@collation_connection */;
/*!50001 SET character_set_client      = utf8mb4 */;
/*!50001 SET character_set_results     = utf8mb4 */;
/*!50001 SET collation_connection      = utf8mb4_general_ci */;
/*!50001 CREATE ALGORITHM=UNDEFINED */
/*!50013 DEFINER=`root`@`localhost` SQL SECURITY DEFINER */
/*!50001 VIEW `get_realtimedata` AS select `weather_measurements`.`id_weather` AS `id_weather`,`weather_measurements`.`temperature` AS `temperature`,`weather_measurements`.`pressure` AS `pressure`,`weather_measurements`.`altitude` AS `altitude`,`weather_measurements`.`air_quality` AS `air_quality`,`weather_measurements`.`date_time` AS `date_time` from `weather_measurements` order by `weather_measurements`.`date_time` desc limit 1 */;
/*!50001 SET character_set_client      = @saved_cs_client */;
/*!50001 SET character_set_results     = @saved_cs_results */;
/*!50001 SET collation_connection      = @saved_col_connection */;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2023-05-28 23:26:14
