
import 'package:flutter/material.dart';
import 'doctorhomepage.dart';
import 'doctorhomepage.dart';


class HomeScreen1 extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: MainScreen(),
      title: 'APPOINTMENTS',
      theme: appTheme,
    );
  }
}

ThemeData appTheme = ThemeData(
  fontFamily: 'Oxygen',
  primaryColor: Colors.red,
);

class MainScreen extends StatefulWidget {
  @override
  _MainScreenState createState() => _MainScreenState();
}

class _MainScreenState extends State<MainScreen> {
  PageController _pageController;

  int _page = 0;

  int index=0;

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        leading: BackButton(
          onPressed: () {
            runApp(new MaterialApp(
              home:MyApp1(),
            ));
          },),
        title: const Text('Patient\'s'),
      ),
      drawer: new Drawer(
          child:ListView(
              children:<Widget>[
                UserAccountsDrawerHeader(
                  accountName: new Text("Dr.Nandu Patahak",style:new TextStyle(fontWeight: FontWeight.bold)),
                  accountEmail:new Text("doctor@gmail.com"),
                  decoration: new BoxDecoration(color: Colors.red),
                ),
                ListTile(
                  leading:Icon(Icons.person),
                  title:Text('Profile'),
                ),
                ListTile(
                  leading:Icon(Icons.vpn_key),
                  title:Text('Password'),
                ),
              ]
          )
      ),
      body: ListView(
        scrollDirection: Axis.vertical,
        children: <Widget>[
          CurvedListItem(
            title: 'Luna Manandhar',
            time: '02:00-03:00pm',
            color: Colors.lightBlueAccent,
            nextColor: Colors.lightBlue,
          ),
          CurvedListItem(
            title: 'Gaurav Jyakhwa',
            time: '04:00-05:00pm',
            color: Colors.lightBlue,
            nextColor: Colors.lightBlueAccent,
          ),
          CurvedListItem(
            title: 'Gopal Baidawar Chetri',
            time: '10:00-11:00am',
            color: Colors.lightBlueAccent,
            nextColor: Colors.lightBlue,
          ),
          CurvedListItem(
            title: 'Kriti Nyoupane',
            time: '11:00am-12:00pm',
            color: Colors.lightBlue,
          ),
        ],
      ),
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

class CurvedListItem extends StatelessWidget {
  const CurvedListItem({
    this.title,
    this.time,
    this.icon,
    this.people,
    this.color,
    this.nextColor,
  });

  final String title;
  final String time;
  final String people;
  final IconData icon;
  final Color color;
  final Color nextColor;

  @override
  Widget build(BuildContext context) {
    return Container(
      color: nextColor,
      child: Container(
        decoration: BoxDecoration(
          color: color,
          borderRadius: const BorderRadius.only(
            bottomLeft: Radius.circular(80.0),
          ),
        ),
        padding: const EdgeInsets.only(
          left: 32,
          top: 80.0,
          bottom: 50,
        ),
        child: Column(
            crossAxisAlignment: CrossAxisAlignment.start,
            children: <Widget>[
              Text(
                time,
                style: TextStyle(color: Colors.white, fontSize: 12),
              ),
              const SizedBox(
                height: 2,
              ),
              Text(
                title,
                style: TextStyle(
                    color: Colors.white,
                    fontSize: 22,
                    fontWeight: FontWeight.bold),
              ),
              Row(),
            ]),
      ),
    );
  }
}