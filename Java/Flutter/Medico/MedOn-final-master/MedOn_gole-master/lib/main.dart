
import 'package:flutter/material.dart';
import 'package:medon99/subscription.dart';
import 'list.dart';
import 'profile.dart';
import 'Medicine.dart';
import 'reminder.dart';
import 'chatMain.dart';
import 'subscription.dart';

void main()=> runApp(MyApp());

class MyApp extends StatefulWidget{
@override
_MyAppState createState()=>_MyAppState();
}
class _MyAppState extends State<MyApp>
{
  int _currentIndex=0;
  final tabs=[
    Center(child:Container(
      width:1000,
      height:1000,
      padding: EdgeInsets.all(10),
      child: ListView(
        children: <Widget>[
      Card(
        margin: EdgeInsets.all(10),
        child:InkWell(
          onTap: (){
           runApp(HomeScreen());
        },
        splashColor: Colors.green,
        child: Center(
        child: Column(
          mainAxisSize: MainAxisSize.min,
        children:<Widget>[
        Icon(Icons.list,
        size: 70,
        color: Colors.red),
        Text('Doctor\'s List',style : new TextStyle(fontSize:17))
      ],
    ),
    ),
    ),
    ),
          Card(
            margin: EdgeInsets.all(10),
            child:InkWell(
              onTap: (){
                runApp(new ChatMain());
              },
              splashColor: Colors.green,
              child: Center(
                child: Column(

                  mainAxisSize: MainAxisSize.min,
                  children:<Widget>[
                    Icon(Icons.message,
                        size: 70,
                        color: Colors.red),
                    Text('Chat',style : new TextStyle(fontSize:17))
                  ],
                ),
              ),
            ),
          ),
          Card(
            margin: EdgeInsets.all(10),
            child:InkWell(
              onTap: (){
                runApp(Medicine());
              },
              splashColor: Colors.green,
              child: Center(
                child: Column(

                  mainAxisSize: MainAxisSize.min,
                  children:<Widget>[
                    Icon(Icons.store,
                        size: 70,
                        color: Colors.red),
                    Text('Medicine',style : new TextStyle(fontSize:17))
                  ],
                ),
              ),
            ),
          ),
          Card(
            margin: EdgeInsets.all(10),
            child:InkWell(
              onTap: (){
                runApp(Reminder());
              },
              splashColor: Colors.green,
              child: Center(
                child: Column(

                  mainAxisSize: MainAxisSize.min,
                  children:<Widget>[
                    Icon(Icons.add_alert,
                        size: 70,
                        color: Colors.red),
                    Text('Reminders and history',style : new TextStyle(fontSize:17))
                  ],
                ),
              ),
            ),
          ),
          Card(
            margin: EdgeInsets.all(10),
            child:InkWell(
              onTap: (){
                runApp(Subscription());
              },
              splashColor: Colors.green,
              child: Center(
                child: Column(

                  mainAxisSize: MainAxisSize.min,
                  children:<Widget>[
                    Icon(Icons.subscriptions,
                        size: 70,
                        color: Colors.red),
                    Text('Annual Subscription',style : new TextStyle(fontSize:17))
                  ],
                ),
              ),
            ),
          ),
          Card(
            margin: EdgeInsets.all(10),
            child:InkWell(
              onTap: (){
                runApp(Profile());
              },
              splashColor: Colors.green,
              child: Center(
                child: Column(

                  mainAxisSize: MainAxisSize.min,
                  children:<Widget>[
                    Icon(Icons.person,
                        size: 70,
                        color: Colors.red),
                    Text('Profile',style : new TextStyle(fontSize:17))
                  ],
                ),
              ),
            ),
          ),
        ],
      ),
    )),
    Center(child:Container(
      width:1000,
      height:1000,
      padding: EdgeInsets.all(10),
      child: ListView(
        children: <Widget>[
          Card(

            margin: EdgeInsets.all(10),
            child:InkWell(
              splashColor: Colors.green,
                child: Row(

                  mainAxisSize: MainAxisSize.min,
                  children:<Widget>[
                    Icon(Icons.call,
                        size:60,
                        color: Colors.red),
                    Text('    98xxxx0xx1',style : new TextStyle(fontSize:17))
                  ],
                ),

            ),
          ),
          Card(

            margin: EdgeInsets.all(10),
            child:InkWell(
              splashColor: Colors.green,
                child: Row(

                  mainAxisSize: MainAxisSize.min,
                  children:<Widget>[
                    Icon(Icons.mail,
                        size: 60,
                        color: Colors.red),
                    Text('    MedOn@gmail.com',style : new TextStyle(fontSize:17))
                  ],
                ),
            ),
          ),


        ],
      ),
    )),
  ];
  @override
  Widget build(BuildContext context){
    return Scaffold(
      appBar: AppBar(
        title: const Text('MedOn'),
        backgroundColor: Colors.red,
      ),
      drawer:new Drawer(
        child: ListView(
            children:<Widget>[
              UserAccountsDrawerHeader(
                accountName: new Text("CLASSIFICATION",style: new TextStyle(fontWeight: FontWeight.bold)),
                decoration:new BoxDecoration(color:Colors.red),
              ),
              /*ListTile(
                title: 
                GestureDetector(
                  //icon:Icon(Icons.person),
                  child: UserAccountsDrawerHeader(
                    otherAccountsPictures: <Widget>[
                      Center(child:CircleAvatar(child:Icon(Icons.person)))
                    ],
                    accountName: new Text("CLASSIFICATION",style: new TextStyle(fontWeight: FontWeight.bold),),
                    decoration:new BoxDecoration(color:Colors.red,),
                  ),
                ),
                
              ),*/
                         
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
      body:
      tabs[_currentIndex],
      bottomNavigationBar : BottomNavigationBar(
        currentIndex: _currentIndex,
        type: BottomNavigationBarType.fixed,
        items: [
          BottomNavigationBarItem(
            backgroundColor: Colors.red,
            icon: Icon(Icons.home),
            title: Text('Home'),
          ),
          BottomNavigationBarItem(
            backgroundColor: Colors.blueGrey,
            icon: Icon(Icons.help),
            title: Text('Help'),
          ),
        ],
        onTap: (index)
        {
          setState(() {
            _currentIndex=index;
          });
        },
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
