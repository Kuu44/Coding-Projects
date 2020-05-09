/*import 'package:app2/registerpage.dart';
import 'package:flutter/material.dart';
import 'package:firebase_auth/firebase_auth.dart';


class LoginScreen extends StatefulWidget {
  @override
  _LoginScreenState createState() => _LoginScreenState();
}

class _LoginScreenState extends State<LoginScreen> {
  String _email, _password;
  
  @override
  Widget build(BuildContext context) {
    //TODO: implement build
    return Scaffold(
      appBar: AppBar(
        title: Text(
          "Login Page",
          style: TextStyle(color: Colors.white,fontSize: 20),
        )
      ),
      body: Container(
        child: Center(
          child: Container(
            width:810, height: 200,
            child: Column(
              mainAxisAlignment: MainAxisAlignment.spaceBetween,
              children: <Widget>[
                TextField(
                  decoration: InputDecoration.collapsed(hintText: "Email",
                  border:UnderlineInputBorder()),
                  onChanged: (value) {
                    this.setState(() {_email=value;});
                    
                  },
                ),
                TextField(
                  decoration: InputDecoration(hintText: "Password",
                  labelText: 'Password',
                  border:UnderlineInputBorder()),
                  obscureText: true,
                  onChanged: (value) {
                    this.setState(() {_password=value;});
                    
                  },
                ),
                RaisedButton(
                  child: Text("Sign In"),
                  onPressed: () {
                    FirebaseAuth.instance.signInWithEmailAndPassword(email: _email,password: _password).then((onValue){
                     // Navigator.of(context)
                    }).catchError((error){
                      debugPrint("Error: "+error);
                    });
                  },
                ),
                RaisedButton(
                  child: Text("Create New Account"),
                  onPressed: () {
                   Navigator.push(context,
                      MaterialPageRoute(builder: (context) => MyHomePage()),
  );
                  },
                )
              ],),
          ),
        )
      )
    );
  }
}*/