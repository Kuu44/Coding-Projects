import 'package:flutter/material.dart';
import 'chatHomePage.dart';

void main()=> runApp(MaterialApp(
home: ChatMain(),
));

class ChatMain extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return new MaterialApp(
      title: "Text Chat",
      home: new ChatHomePage(),
      
    );
  }
}