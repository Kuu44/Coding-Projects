import 'loginPage.dart';
import 'package:flutter/material.dart';
//import 'package:firebase_auth/firebase_auth.dart';
//import 'loginpage.dart';
//import 'home.dart';
class MyHomePage extends StatefulWidget {

  MyHomePage({Key key, this.title}) : super(key: key);

  
  final String title;

  @override

  _MyHomePageState createState() => _MyHomePageState();

}

class MyApp2 extends StatelessWidget {

  // This widget is the root of your application.

  @override

  Widget build(BuildContext context) {

    return MaterialApp(

      title: 'Flutter login UI',

      theme: ThemeData(

        primarySwatch: Colors.blue,

      ),

      home: MyHomePage(title: 'Flutter Login'),

    );

  }

}

class _MyHomePageState extends State<MyHomePage> {

  TextStyle style = TextStyle(fontFamily: 'Montserrat', fontSize: 20.0);

  @override

  Widget build(BuildContext context) {

    //Container(child: AssetImage(),)

    final emailField = TextField(

      obscureText: false,

      style: style,

      decoration: InputDecoration(

          contentPadding: EdgeInsets.fromLTRB(20.0, 15.0, 20.0, 15.0),

          hintText: "Email",

          border:

          OutlineInputBorder(borderRadius: BorderRadius.circular(32.0))),

    );

    final firstname = TextField(

      obscureText: false,

      style: style,

      decoration: InputDecoration(

          contentPadding: EdgeInsets.fromLTRB(20.0, 15.0, 20.0, 15.0),

          hintText: "Firstname",

          border:

          OutlineInputBorder(borderRadius: BorderRadius.circular(32.0))),

    ); final secondname = TextField(

      obscureText: false,

      style: style,

      decoration: InputDecoration(

          contentPadding: EdgeInsets.fromLTRB(20.0, 15.0, 20.0, 15.0),

          hintText: "Lastname",

          border:

          OutlineInputBorder(borderRadius: BorderRadius.circular(32.0))),

    );

    final contact = TextField(

      obscureText: false,

      style: style,

      decoration: InputDecoration(

          contentPadding: EdgeInsets.fromLTRB(20.0, 15.0, 20.0, 15.0),

          hintText: "Contact",

          border:

          OutlineInputBorder(borderRadius: BorderRadius.circular(32.0))),

    );

    final passwordField = TextField(

      obscureText: true,

      style: style,

      decoration: InputDecoration(

          contentPadding: EdgeInsets.fromLTRB(20.0, 15.0, 20.0, 15.0),

          hintText: "Password",

          border:
            OutlineInputBorder(borderRadius: BorderRadius.circular(32.0))
          ),
      

    );

    final loginButon = Material(

      elevation: 5.0,

      borderRadius: BorderRadius.circular(30.0),

      color: Colors.red[800],

      child: MaterialButton(

        minWidth: MediaQuery.of(context).size.width,

        padding: EdgeInsets.fromLTRB(20.0, 15.0, 20.0, 15.0),

        onPressed: () {
          runApp( MedON());
        },

        child: Text("Register",

            textAlign: TextAlign.center,

            style: style.copyWith(

                color: Colors.white, fontWeight: FontWeight.bold)),

      ),

    );



    return Scaffold(

      body: Center(

        child: Container(

          padding:EdgeInsets.all(10),

          color: Colors.grey[200],

          child: Padding(

            padding: const EdgeInsets.all(36.0),

            child: Column(

              crossAxisAlignment: CrossAxisAlignment.center,

              mainAxisAlignment: MainAxisAlignment.center,

              children: <Widget>[

                SizedBox(height: 25.0),

                emailField,

                SizedBox(height: 25.0),

                firstname,

                SizedBox(height: 25.0),

                secondname,

                SizedBox(height: 25.0),

                contact,

                SizedBox(height: 25.0),

                passwordField,

                SizedBox(

                  height: 25.0,

                ),

                loginButon,

                SizedBox(

                  height: 15.0,

                ),

              ],

            ),



          ),

        ),

      ),

    );



  }

}