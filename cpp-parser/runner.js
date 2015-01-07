var path = require('path');
var util=require('util')
var exec=require('child_process').exec;
var fs = require('fs');
var argv = process.argv;
var inspect = util.inspect;
var memory = require('copy-paste');

if (argv.length < 3) {
  console.log('Usage: node runner.js <io_file>');
  return;
} 

var filename = argv[2];
var statFile = path.resolve(__dirname, filename + '_stat');

fs.exists(statFile, function (exists) {
  var idx = 0;
  util.debug(exists ? "it's exists!" : "no stat file");
  if (!exists) return execute(filename, idx, statFile);

  fs.readFile(statFile, function(err, idx) {
    if (err) throw err;
    idx = parseInt(idx);
    execute(filename, idx, statFile);  
  });
});


function execute(filename, idx, statFile) {
  var base_command = 'cat ' + filename + ' | sed -n ' + idx + 'p';
  var notifier = 'terminal-notifier -title "Mailer Clipboard Helper" -message ';
  cmdProcess(base_command, function(err, stdout, stderr) {
    notifier += '"' + stdout + ' copied (' + idx + ' entry)"';
    console.log('Copied to clipboard (' + idx + ' addr) : ', stdout);
    cmdProcess(notifier,
      memory.copy(stdout, writeStats(statFile, idx + 1)));
  });
}

function writeStats(statFile, data) {
  return (function() {
    fs.writeFile(statFile, data, function(err) {
      if (err) throw err;
      console.log('Statistics saved in ' + statFile);
    }); 
  });
}

function cmdProcess(command, callback) {
  exec(command, callback);
}

/*exec('ls -al',function(err,stdout,stderr){
    util.puts("hello")
    util.puts(stdout)
})*/
