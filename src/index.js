
//import {http} from "./app";
import { app, http } from "./app";

const main = () => {
    http.listen(app.get('port'), () => {
        console.log("This is the socket server running at port ",app.get('port'));
      });
}
main();

