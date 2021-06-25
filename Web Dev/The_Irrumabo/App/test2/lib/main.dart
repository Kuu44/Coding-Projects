import 'package:flutter/material.dart';
import 'package:flutter/foundation.dart';
//import 'package:flutter/services.dart' show rootBundle;

void main() => runApp(const MyApp());

class MyApp extends StatelessWidget {
 const MyApp();

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      theme: ThemeData(
        primarySwatch: Colors.deepOrange,
      ),
      home: const MyHomePage(),
    );
  }
}

class Kitten{
  const Kitten({this.name, this.description, this.age, this.imageUrl});

  final String name;
  final String description;
  final int age;
  final String imageUrl;
}

final String server=
    defaultTargetPlatform==TargetPlatform.android ? "10.0.2.2" : "localhost";

final List<Kitten> kittens = <Kitten>[
  Kitten(
    name: 'Goley',
    description: 'Nakhey '
      'Jhagadey.',
    age: 0,
    imageUrl: 'https://scontent.fktm4-1.fna.fbcdn.net/v/t1.0-1/81054687_3289139064489572_488648436539719680_o.jpg?_nc_cat=109&_nc_ohc=PqTr44Uba7IAX9faeXS&_nc_ht=scontent.fktm4-1.fna&oh=fd2860b8ab5d2ecf57890c95da461e95&oe=5EDB06A2'),
  Kitten(
    name: 'Kirey',
    description: 'Alxi '
      'Photographer.',
    age: 20,
    imageUrl: 'https://scontent.fktm4-1.fna.fbcdn.net/v/t31.0-8/27907627_1876507522598817_5723504262314663076_o.jpg?_nc_cat=106&_nc_ohc=YigjBRXDrSEAX9q6KYA&_nc_ht=scontent.fktm4-1.fna&oh=0e1c0427a3d20e472cbe2fc9748ce1b6&oe=5ECB6F21'),
  Kitten(
    name: 'Kriti',
    description: 'Nautanki '
      'Chatakeyyy.',
    age: 21,
    imageUrl: 'https://scontent.fktm4-1.fna.fbcdn.net/v/t1.0-9/10458443_769331053194787_5591016255223287438_n.jpg?_nc_cat=106&_nc_ohc=Tdwqv0tLQmkAX_tqXVZ&_nc_ht=scontent.fktm4-1.fna&oh=a1ee375b13b4d8cfcfffdf5fe496b81b&oe=5EDB4CC3'),
  Kitten(
    name: 'Manjeet',
    description: 'Bhauju wala '
      'Dudey.',
    age: 20,
    imageUrl: 'https://scontent.fktm4-1.fna.fbcdn.net/v/t1.0-9/47222062_964694313721174_5125682699113070592_n.jpg?_nc_cat=111&_nc_ohc=tqF-2NKGVM4AX_lboN6&_nc_ht=scontent.fktm4-1.fna&oh=444eb7085faa57e849adc6d97283e2a8&oe=5ECDB768'),
];

class MyHomePage extends StatelessWidget {
  const MyHomePage({Key key}) : super(key: key);

  Widget _dialogBuilder(BuildContext context, Kitten kitten){
    return SimpleDialog(
      contentPadding: EdgeInsets.zero,
      children: [
        /*Image(
          image: AssetImage('assets/file1.png'),
        ),*/
        Image.network(
        kitten.imageUrl,
      fit: BoxFit.fill,
    ),
        Padding(
          padding: const EdgeInsets.all(16.0),
          child: Column(
            children: [
              Text (kitten.name),
              Text ('${kitten.age} years old'),
              Text (kitten.description),
            ]
          )
        )
    ],
    );
  }

  Widget _listItemBuilder(BuildContext context, int index){
    return new GestureDetector(
      onTap: () => showDialog(
          context: context,
          builder: (context) => _dialogBuilder(context, kittens[index])),
      child: Container(
          padding: const EdgeInsets.only(left: 16.0),
          alignment: Alignment.center,
          child: Text(kittens[index].name,
          style: Theme.of(context).textTheme.headline),
      ),
    );
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
        appBar: AppBar(
          title: Text('Namuna Haru')
        ),
        body: ListView.builder(
          itemCount: kittens.length,
          itemExtent: 60.0,
          itemBuilder: _listItemBuilder,
        )
      );
  }
}
