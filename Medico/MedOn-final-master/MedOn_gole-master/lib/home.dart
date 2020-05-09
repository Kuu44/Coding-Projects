/*
import 'package:flutter/material.dart';
import 'package:firebase_auth/firebase_auth.dart';
import 'home.dart';
import 'loginScreen.dart';

void main() {
  runApp(new MaterialApp(
    title: 'MedOn App',
    home:_handleWindowDisplay(),
));
}

Widget _handleWindowDisplay(){
  return StreamBuilder(
    stream: FirebaseAuth.instance.onAuthStateChanged,
    builder: (BuildContext context,snapshot){
      if(snapshot.connectionState == ConnectionState.waiting){
        return Center(child: Text("Loading..."));
      }
      else{
        if(snapshot.hasData){
          return MyApp();
        }
        else{
          return LoginScreen();
        }
      }
},);
}
*/