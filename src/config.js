import { config } from "dotenv";
config();
export default {

    host: process.env.HOST || "localhost", //
    database: process.env.DATABASE || "EstacionMeteorologico",
    user: process.env.USER || "estacion",
    password: process.env.PASSWORD || "mysql_MAO97"
}
/* 
export default {

    host: process.env.HOST || "localhost", //
    database: process.env.DATABASE || "EstacionMeteorologico",
    user: process.env.USER || "root",
    password: process.env.PASSWORD || "mysql_MAO97" "R5c2$5nq0"
}
*/