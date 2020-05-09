import 'package:flutter/material.dart';
import 'main.dart';
import 'list.dart';


class Medicine extends StatefulWidget
{
  @override
  _MedicineState createState() => _MedicineState();
}

class _MedicineState extends State<Medicine> {
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
            "MedOn Pharmacy ",
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
                      Icon(Icons.healing,
                          size:60,
                          color: Colors.red),
                      Text('    Paracetamol   (Rs20)',style : new TextStyle(fontSize:17))
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
                      Icon(Icons.healing,
                          size:60,
                          color: Colors.red),
                      Text('    Rinex  (Rs25)',style : new TextStyle(fontSize:17))
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
                      Icon(Icons.healing,
                          size:60,
                          color: Colors.red),
                      Text('    Myodip5 (Rs110)',style : new TextStyle(fontSize:17))
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
                      Icon(Icons.healing,
                          size:60,
                          color: Colors.red),
                      Text('    Odomous  (Rs80)',style : new TextStyle(fontSize:17))
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