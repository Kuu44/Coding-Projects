import 'package:flutter/material.dart';
import 'chat.dart';
import 'doctorhomepage.dart';
import 'main.dart';


class ChatHomePage extends StatefulWidget {
  @override
  _ChatHomePageState createState() => _ChatHomePageState();
}

class _ChatHomePageState extends State<ChatHomePage> {
  @override
  Widget build(BuildContext context) {
    return new Scaffold(
      appBar: new AppBar(
        leading: BackButton(
          onPressed: () {
            runApp(new MaterialApp(
            home: MyApp(),
          ));
          },),
        title: new Text('Dr.Nandu Pathak'),
        centerTitle: true,
        backgroundColor: Colors.redAccent,
        actions: <Widget>[
          RaisedButton(onPressed: (){},child:Icon(Icons.videocam),color: Colors.redAccent,),
        ],
      ),
      body: new ChatScreen(),
      /*floatingActionButton: FloatingActionButton(
          onPressed: (){
            runApp(new MaterialApp(
              home:MyApp(),
            ));
          },
          child:Icon(Icons.arrow_back),
          backgroundColor: Colors.red,

        ),*/
    );
  }
}