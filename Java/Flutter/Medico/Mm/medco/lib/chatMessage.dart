import 'package:flutter/material.dart';
//import 'package:flutter/chat.dart';


String _name ="Luna Manandhar";


class ChatMessage extends StatefulWidget {
  final String text;
ChatMessage({this.text});

  @override
  _ChatMessageState createState() => _ChatMessageState();
}

class _ChatMessageState extends State<ChatMessage> {
  @override
  Widget build(BuildContext context) {
    return new Container(
      margin: const EdgeInsets.symmetric(vertical: 10.0),
      child: new Row(
        crossAxisAlignment: CrossAxisAlignment.end,
        children: <Widget>[
          new Container(
            margin: const EdgeInsets.only(right: 15.0),
            child: new CircleAvatar(
              child: new Text(_name[0]),
            ),
          ),
          new Column(
            crossAxisAlignment: CrossAxisAlignment.start,
            children: <Widget>[
              new Text(_name, style:Theme.of(context).textTheme.subhead),
              new Container(
                margin: const EdgeInsets.only(top: 10.0),
                child: new Text(widget.text),
              ),
            ],
          )

        ],
      ),
      
    );
  }
}