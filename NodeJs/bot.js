// require the discord.js module
const fs = require('fs');
const Discord = require('discord.js');
const keepAlive=require('./server');

const {prefix} = require('./auth.json');
const {token} = require('./secrets.json');

// Initialize Discord Bot
const bot = new Discord.Client();
bot.commands = new Discord.Collection();

var {info:infos} = require('./info.js');
var schedule = require("node-schedule");
const scheduleNotification=require("./functions/scheduleNotifications.js")

const commandFiles = fs.readdirSync('./commands').filter(file => file.endsWith('.js'));
for (const file of commandFiles) {
  const command = require(`./commands/${file}`);

  //setting a new item in the collection
  bot.commands.set(command.name, command);
}

//for help.js
const helpCommand = require('./functions/help.js');
bot.commands.set(helpCommand.name, helpCommand);

keepAlive();

bot.login(token);
//bot.login(process.env.BOT_TOKEN);
//Bot commands

let logChannel;
bot.channels.cache.map((channel) => {
  if (channel.id == '763767420908732448') {
    logChannel=channel;
  }
});

bot.once('ready', () => { //Only triggers once after logging in
  console.log('Ready!');

    for(const serverId in infos)
    {
      let info=infos[serverId]
      //console.log(info[property].channelId)
      bot.channels.cache.map((channel)=>{
      if(channel.id==info.channelId) {
      console.log(channel.name);
      //channel.send(" Sorry I was asleep :sweat_smile: I'm awake now !");
        try{
          scheduleNotification(channel,info,schedule,serverId,bot);
        }catch(e)
        {
          console.log(e);
          logChannel.send(`Error scheduling! in ${channel.guild.name}'s ${channel.name}`);
        }
      }
    });
    }
});

bot.on('message', message => {
  //logs everything typed
  //console.log(message.content);

  if (!message.content.startsWith(prefix) || message.author.bot) return;

  var args = message.content.slice(prefix.length).trim().split(/ +/);
  var commandName = args.shift().toLowerCase();

  if (!bot.commands.has(commandName)) return message.channel.send(`Hmm I dont seem to have this command, ${message.author}!:sweat_smile:\nTry **rt! help** for more details!`);
  const command = bot.commands.get(commandName);
  if (command.args && !args.length) {
    return message.channel.send(`You didn't provide any argument, ${message.author} :sweat_smile:!\nUsage: ${command.usage}`);
  }
  try {
    command.execute(message, args, bot);
  } catch (error) {
    console.error(error);
    message.reply('There was an error trying to execute that command! :sweat_smile:');
  }
});
