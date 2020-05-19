import 'package:flutter/material.dart';
import 'main.dart';


class Subscription extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: MainScreen(),
      title: 'Annual Subscription Package',
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
              home: MyApp(),
            ));
          },),
        title: const Text('Annual Subscription Package'),
      ),
      body: ListView(
        scrollDirection: Axis.vertical,
        children: <Widget>[
          CurvedListItem(
            title: 'DR.NANDU PATHAK',
            time: 'PHYSICIAN(Rs 4500)',
            color: Colors.blue[300],
            nextColor: Colors.blue,
          ),
          CurvedListItem(
            title: 'DR.RITIKA RIJAL ',
            time: 'NEUROSURGEON(Rs5000)',
            color: Colors.blue[300],
            nextColor: Colors.blue,
          ),
          CurvedListItem(
            title: 'DR. SHRAWAN KUMAR',
            time: 'GYNECOLOGIST(Rs3000',
            color: Colors.blue[300],
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