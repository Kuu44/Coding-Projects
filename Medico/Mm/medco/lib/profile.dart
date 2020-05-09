import 'loginpage.dart';
import 'package:flutter/material.dart';
import 'main.dart';
import 'list.dart';


class Profile extends StatefulWidget {
  @override
  _ProfileState createState() => _ProfileState();
}

class _ProfileState extends State<Profile> {
  @override
  Widget build(BuildContext context) {
    // TODO: implement build
    return MaterialApp(
      home: Scaffold(
        appBar: AppBar(
          leading: BackButton(
          onPressed: () {
            runApp(new MaterialApp(
            home: MyApp(),
          ));
          },),
          title: Text(
            "Profile ",
            style: TextStyle(fontSize: 18.0),
          ),
          backgroundColor: Colors.red,
        ),
        drawer:new Drawer(
            child: ListView(
                children:<Widget>[
                  UserAccountsDrawerHeader(
                    accountName: new Text("CLASSIFICATION",style: new TextStyle(fontWeight: FontWeight.bold)),
                    decoration:new BoxDecoration(color:Colors.red),
                  ),
                  ListTile(
                      title: GestureDetector(
                        onTap: () => showDialog(
                          context:context,
                          builder:(context) =>_dialogBuilder(context, doctors[0]),
                        ),
                        child: Text('PHYSICIAN'),
                      )
                  ),
                  ListTile(
                      title: GestureDetector(
                        onTap: () => showDialog(
                          context:context,
                          builder:(context) =>_dialogBuilder(context, doctors[1]),
                        ),
                        child: Text('NEUROSURGEON'),
                      )
                  ),
                  ListTile(
                      title: GestureDetector(
                        onTap: () => showDialog(
                          context:context,
                          builder:(context) =>_dialogBuilder(context, doctors[3]),
                        ),
                        child: Text('GYNECOLOGIST'),
                      )
                  ),
                  ListTile(
                      title: GestureDetector(
                        onTap: () => showDialog(
                          context:context,
                          builder:(context) =>_dialogBuilder(context, doctors[2]),
                        ),
                        child: Text('PSYCHIATRIST'),
                      )
                  ),



                ]
            )

        ),
        body: SafeArea(
          child: Center(
            child: Column(
              mainAxisAlignment: MainAxisAlignment.center,
              children: <Widget>[
              CircleAvatar(child:Icon(Icons.person,size:40.0),radius: 60.0,),
                Text(
                  'Luna Manandhar',
                  style: TextStyle(
                    fontSize: 20,
                    fontFamily: 'SourceSansPro',
                    color: Colors.black,
                    letterSpacing: 2.5,
                  ),
                ),
                SizedBox(
                  height: 20.0,
                  width: 200,
                  child: Divider(
                    color: Colors.teal[100],
                  ),
                ),
                Card(
                    color: Colors.white,
                    margin:
                    EdgeInsets.symmetric(vertical: 10.0, horizontal: 25.0),
                    child: ListTile(
                      leading: Icon(
                        Icons.phone,
                        color: Colors.teal[900],
                      ),
                      title: Text(
                        '+977 98xxxx0x32',
                      ),
                    )),
                    RaisedButton(
                      child: Text('Log Out'),
                      onPressed: () {
                       runApp(MedON());
                      },
                    )

              ],
            ),
          ),
        ),
       /*floatingActionButton: FloatingActionButton(
         onPressed: (){
           runApp(new MaterialApp(
             home:MyApp(),
           ));
         },
        child:Icon(Icons.arrow_back),
         backgroundColor: Colors.red,

       ),*/

      ),
    );
  }
}
Widget _dialogBuilder(BuildContext context,Doctor doctor){

  return SimpleDialog(
      contentPadding: EdgeInsets.all(5.0),
      children:[
        //Image.asset(),
        Padding(
          padding: const EdgeInsets.all(5.0),
          child: Column(
            children: [
              Text(doctor.name),
              Text('RS ${doctor.charge}'),
              Text(doctor.occupation),
            ],
          ),
        ),
      ]
  );
}

