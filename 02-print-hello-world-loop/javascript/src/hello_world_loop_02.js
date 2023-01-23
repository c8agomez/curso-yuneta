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
    const time = process.hrtime();
    const NS_PER_SEC = 1e9;
    const MS_PER_NS = 1e-6
    //const time = process.hrtime(); TODO otro método
    // bucle
    for (let i=1;i<=repeat; i++) {
        console.log('Hello World',i);
    }

    //Fin tiempo
    //   const end = process.hrtime(start); TODO otro método

    //Impresión tiempo tardado
    //   console.log(`Spent time ${((end[0])+(end[1])/1000000000).toFixed(3)}s. to print ${repeat} times.`) TODO otro método
    const diff = process.hrtime(time);
    console.log(`Spent time ${ (((diff[0] * NS_PER_SEC + diff[1])  * MS_PER_NS)/1000).toFixed(3) } s. to print ${repeat} times.`)
}

main ();
