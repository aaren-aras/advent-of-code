import fs from 'fs';

fs.readFile('cube-conundrum.txt', 'utf8', (err, data) => {
  if (err) {
    console.error(err);
    return;
  }

  const games = data.split('\n'); 
  const powerSum = games.reduce((acc, cur) => {
    let maxRedCubes = Math.max(...cur.match(/..(?=\sred)/g)); 
    let maxGreenCubes = Math.max(...cur.match(/..(?=\sgreen)/g));
    let maxBlueCubes = Math.max(...cur.match(/..(?=\sblue)/g));

    return acc + (maxRedCubes * maxGreenCubes * maxBlueCubes);
  }, 0);
  console.log(powerSum) // Output: 
});