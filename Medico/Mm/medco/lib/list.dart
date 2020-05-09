import 'package:flutter/material.dart';
import 'main.dart';


class HomeScreen extends StatelessWidget {
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
    String gf='Physician';
    return Scaffold(
      appBar: AppBar(
        leading: BackButton(
          onPressed: () {
            runApp(new MaterialApp(
            home: MyApp(),
          ));
          },),
        title: const Text('APPOINTMENTS'),
      ),
      drawer:new Drawer(
          child: ListView(
              children:<Widget>[
                UserAccountsDrawerHeader(
                  accountName: new Text("CLASSIFICATION",style: new TextStyle(fontWeight: FontWeight.bold)),
                  decoration:new BoxDecoration(color:Colors.red),
                ),


                ListTile(
                    title: GestureDetector(
                      onTap: () => showDialog(
                        context:context,
                        builder:(context) =>_dialogBuilder(context,doctors[0]),
                      ),
                      child: Text('PHYSICIAN'),
                    )
                ),
                ListTile(
                    title: GestureDetector(
                      onTap: () => showDialog(
                        context:context,
                        builder:(context) =>_dialogBuilder(context,doctors[1]),
                      ),
                      child: Text('NEUROSURGEON'),
                    )
                ),
                ListTile(
                    title: GestureDetector(
                      onTap: () => showDialog(
                        context:context,
                        builder:(context) =>_dialogBuilder(context, doctors[3]),
                      ),
                      child: Text('GYNECOLOGIST'),
                    )
                ),
                ListTile(
                    title: GestureDetector(
                      onTap: () => showDialog(
                        context:context,
                        builder:(context) =>_dialogBuilder(context, doctors[2]),
                      ),
                      child: Text('PSYCHIATRIST'),
                    )
                ),



              ]
          )

      ),
      body: ListView(
        scrollDirection: Axis.vertical,
        children: <Widget>[
          CurvedListItem(
            title: 'DR.NANDU PATHAK',
            time: 'PHYSICIAN',
            color: Colors.lightBlueAccent,
            nextColor: Colors.lightBlue,
          ),
          CurvedListItem(
            title: 'DR.RITIKA RIJAL ',
            time: 'NEUROSURGEON',
            color: Colors.lightBlue,
            nextColor: Colors.blue,
          ),
          CurvedListItem(
            title: 'DR. SHRAWAN KUMAR',
            time: 'GYNECOLOGIST',
            color: Colors.blue,
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
Widget _dialogBuilder(BuildContext context,Doctor doctor){

  return SimpleDialog(
      contentPadding: EdgeInsets.all(5.0),
      children:[
        //Image.asset(),
        Padding(
          padding: const EdgeInsets.all(5.0),
          child: Column(
            children: [
              Text(doctor.name),
              Text('RS ${doctor.charge}'),
              Text(doctor.occupation),
            ],
          ),
        ),
      ]
  );
}
class Doctor{
  const Doctor({this.name, this.occupation,this.charge});
  final String name;
  final String occupation;
  final int charge;
}
final List<Doctor> doctors= <Doctor>[
  Doctor(
      name:'Dr.Nandu Pathak',
      occupation: 'Physician',
      charge: 250
  ),
  Doctor(
      name:'Dr.Ritika Rijal',
      occupation: 'Neurosurgeon',
      charge: 300
  ),
  Doctor(
      name:'Dr.Shrawan Kumar',
      occupation: 'Psychatrist',
      charge: 300
  ),
  Doctor(
      name:'Dr.Manjeet Pandey',
      occupation: 'Gynecologist',
      charge: 300
  ),
];



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