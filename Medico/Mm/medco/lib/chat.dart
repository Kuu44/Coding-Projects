import 'chatMessage.dart';
import 'package:flutter/material.dart';
//import 'main.dart';



class ChatScreen extends StatefulWidget {
  @override
  _ChatScreenState createState() => _ChatScreenState();
}

class _ChatScreenState extends State<ChatScreen> {
  
final TextEditingController _textController = new TextEditingController();
final List<ChatMessage> _messages = <ChatMessage> [];



void _handleSubmitted(String text){
  _textController.clear();
  ChatMessage message = new ChatMessage(
    text: text,
  );
  setState(() {
    _messages.insert(0, message);
  });
}

  Widget _textComposureWidget(){
    return new IconTheme(
      data: new IconThemeData(
        color: Colors.red,
      ),
          child: new Container(
        margin: const EdgeInsets.symmetric(horizontal:8.0),
        child: new Row(
          children: <Widget>[
            new Flexible(
              child: new TextField(
                decoration:
                 new InputDecoration.collapsed(
                hintText: 'Send a Message.'),
              controller: _textController,
              onSubmitted:  _handleSubmitted,
              ),
            ),
            new Container(
              margin: const EdgeInsets.symmetric(horizontal: 4.0),
              child: new IconButton(
                icon: Icon(Icons.send),
                onPressed: () => _handleSubmitted(_textController.text),
                
              )
            )
        ],)
      ),
    );
  }
  
  @override 
  Widget build(BuildContext context) {
    return new Column(
        children: <Widget>[
          new Flexible(
            child: new ListView.builder(
              padding: new EdgeInsets.all(8.0),
              reverse: true,
              itemBuilder: (_,int index) => _messages[index],
              itemCount: _messages.length,
              ),
           ),
          new Divider(height: 1.0,),
          new Container(
            decoration: BoxDecoration(
              color: Theme.of(context).cardColor,
            ),
            child: _textComposureWidget(),
          )

        ],
      );
    /*Scaffold(
    appBar: AppBar(
        title: const Text('Chat Screen'),
      ),
      drawer:new Drawer(
      child: ListView(
        children:<Widget>[
          new UserAccountsDrawerHeader(
            accountName: new Text("CLASSIFICATION",style: new TextStyle(fontWeight: FontWeight.bold)),
            decoration:new BoxDecoration(color:Colors.red),
            ),
          ],
        ),
      ),
      body:
    );*/
  }
}