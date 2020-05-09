import 'package:flutter/material.dart';
import 'package:flutter/cupertino.dart';
import 'package:flutter/services.dart';
import 'main.dart';
import 'doctorhomepage.dart';
import 'registerpage.dart';
void main()
{
  runApp(new MedON());
}
class MedON extends StatelessWidget
{
  @override
  Widget build(BuildContext context)
  {
    return new MaterialApp
      (
      title: "MedOn",
      theme: new ThemeData
        (
        primarySwatch:Colors.red,
      ),
      home:Loginregister(),
    );
  }
}

class Loginregister extends StatefulWidget{

  State<StatefulWidget>createState()
  {
    return LoginregisterState();
  }
}
enum FormType
{
  login,
  register
}
class LoginregisterState extends State<Loginregister> {

  final formKey = new GlobalKey<FormState>();
  FormType _formType = FormType.login;
  String _email = "";
  String _password = "";

  bool validateandsave() {
    final form = formKey.currentState;
    if (form.validate()) {
      form.save();
      return true;
    }
    else
    {
      return false;
    }
  }
  void movetoregister() {
    formKey.currentState.reset();
    setState(() {
      _formType = FormType.register;
    });
  }

  void movetologin() {
    formKey.currentState.reset();
    setState(() {
      _formType = FormType.login;
    });
  }

  @override
  Widget build(BuildContext context) {
    return new Scaffold
      (
      appBar: new AppBar
        (
        title: new Center(child: new Text("MedOn", textAlign: TextAlign.center)),
      ),

      body: new SafeArea(
        top: false,
        bottom: false,
        child: new Form(
          key: formKey,
          child: new ListView(
            children: createInputs() + createButtons(),
          ),
        ),
      ),);
  }

  List<Widget> createInputs() {
    return
      [
        new CircleAvatar(
          backgroundColor: Colors.transparent,
          radius: 110.0,
          child: Image(image: AssetImage('assets/lo.png')),
        ),
        new TextFormField(
          decoration: const InputDecoration(
              icon: const Icon(Icons.person),
              hintText: 'Put a valid e-mail',
              labelText: 'E-mail'),
          inputFormatters: [new LengthLimitingTextInputFormatter(30)],
          validator: (val)
          {
            return val.isEmpty ? 'Email is required' : null;
          },
          onSaved: (val) {
            return _email = val;
          },
        ),

        new TextFormField(
          decoration: const InputDecoration(
              icon: const Icon(Icons.security),
              hintText: 'Enter a password',
              labelText: 'Password'),
          obscureText: true,
          validator: (val)
          {
            return val.isEmpty ? 'Password is required' : null;
          },
          onSaved: (val) {
            print(_password);
            return _password = val;
          },
        ),

      ];
  }

  List<Widget> createButtons() {
    if(_formType==FormType.login)
    {
      return
        [

          SizedBox(height: 20.0),
          RaisedButton(
            color: Colors.red,
            child: Text(
              'Login',
              style: TextStyle(color: Colors.white),
            ),
            onPressed: () {
              if (_email=='medon.doctor@gmail.com' && _password=='visitnepal2020') {
                runApp(new MaterialApp(
                  home: MyApp1(),
                ));
              }
                else if (_email=='medon.patient@gmail.com' && _password=='visitnepal2020') {
                runApp(new MaterialApp(
                  home: MyApp(),
                ));
              }
                         
              else {
                print(_email);
                runApp(new MaterialApp(
                  home: MyApp(),
                ));
              }
            }
          ),
          FlatButton(
            color: Colors.red,
            child: Text(
              'Not have an account? Create Account',
              style: TextStyle(color: Colors.white),
            ),
            onPressed:()
              {
                runApp(MyApp2());
              }
          ),
        ];
    }
    else
    {
      return
        [
          SizedBox(height: 20.0),
          RaisedButton(
            color: Colors.blue[400],
            child: Text(
              'Register',
              style: TextStyle(color: Colors.white),
            ),
            onPressed: validateandsave,
          ),
          FlatButton(
            color: Colors.blue[400],
            child: Text(
              'Already have a account?Login',
              style: TextStyle(color: Colors.white),
            ),
            onPressed: movetologin,
          ),
        ];
    }
  }
}


