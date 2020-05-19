import 'package:flutter/material.dart';
import 'main.dart';
import 'list.dart';


class Reminder extends StatefulWidget
{
  @override
  _ReminderState createState() => _ReminderState();
}

class _ReminderState extends State<Reminder> {
  @override
  Widget build(BuildContext context)
  {
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
            "Reminder and History ",
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
        body:  Center(child:Container(
          width:1000,
          height:1000,
          padding: EdgeInsets.all(10),
          child: ListView(
            children: <Widget>[
              Card(

                margin: EdgeInsets.all(10),
                child:InkWell(
                  onTap:()
                  {

                  },
                  splashColor: Colors.green,
                  child: Row(

                    mainAxisSize: MainAxisSize.min,
                    children:<Widget>[
                      Icon(Icons.add_alert,
                          size:60,
                          color: Colors.red),
                      Text('Checkup date:2019/12/01',style : new TextStyle(fontSize:17))
                    ],
                  ),

                ),
              ),
              Card(
                margin: EdgeInsets.all(10),
                child:InkWell(
                  onTap:()
                  {

                  },
                  splashColor: Colors.green,
                  child: Row(

                    mainAxisSize: MainAxisSize.min,
                    children:<Widget>[
                      Icon(Icons.add_alert,
                          size:60,
                          color: Colors.red),
                      Text('Checkup date:2019/11/01',style : new TextStyle(fontSize:17))
                    ],
                  ),
                ),
              ),
              Card(
                margin: EdgeInsets.all(10),
                child:InkWell(
                  onTap:()
                  {

                  },
                  splashColor: Colors.green,
                  child: Row(

                    mainAxisSize: MainAxisSize.min,
                    children:<Widget>[
                      Icon(Icons.add_alert,
                          size:60,
                          color: Colors.red),
                      Text('Checkup date:2019/10/01',style : new TextStyle(fontSize:17))
                    ],
                  ),
                ),
              ),
              Center(child:Text('Follow Up ',textScaleFactor: 1.0,),),
              Card(
                margin: EdgeInsets.all(10),
                child:InkWell(
                  onTap:()
                  {

                  },
                  splashColor: Colors.green,
                  child: Row(

                    mainAxisSize: MainAxisSize.min,
                    children:<Widget>[
                      Icon(Icons.add_alert,
                          size:60,
                          color: Colors.red),
                      Text('Followup chekup:2020/01/01',style : new TextStyle(fontSize:17))
                    ],
                  ),
                ),
              ),
            ],
          ),
        )),
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