#!/usr/bin/env node

const { Command } = require('commander');
const program = new Command();

function main() {
  var repeat = 100;

// Opciones

  program
    .name('string-util')
    .description('Hello world loop')
    .version('1.0.0')
    .usage('[-h] [-v] [-r REPEAT]')
    .option('-r, --repeat <REPEAT>', 'N times repeat "Hello world". (Default=100)', parseInt)
    .parse(process.argv);

  const options = program.opts();

  if (options.repeat) {
      repeat=options.repeat
  }

//Inicio tiempo
  const start = process.hrtime();

// bucle
  for (let i=1;i<=repeat; i++) {
      console.log('Hello World',i);
  }
//Fin tiempo
  const end = process.hrtime(start);

//Impresión tiempo tardado
  console.log(`Spent time ${(end[0] +(end[1]/1000000)).toFixed(3)}s. to print ${repeat} times.`)
}

main ();
