import fs from 'fs';

fs.readFile('cube-conundrum.txt', 'utf8', (err, data) => {
  if (err) {
    console.error(err);
    return;
  } 
  
  const games = data.split('\n'); 
  const idSum = games.reduce((acc, cur, i) => {
    let redCubes = cur.match(/..(?=\sred)/g); // Use positive lookahead to select 2 chars before " red"
    let greenCubes = cur.match(/..(?=\sgreen)/g);
    let blueCubes = cur.match(/..(?=\sblue)/g);

    let maxRedCubes = Math.max(...redCubes); // Spread array elements into individual arguments for `max()` func
    let maxGreenCubes = Math.max(...greenCubes);
    let maxBlueCubes = Math.max(...blueCubes);

    if (maxRedCubes <= 12 && maxGreenCubes <= 13 && maxBlueCubes <= 14) return acc + i + 1;
    else return acc; 
  }, 0);
  console.log(idSum) // Output: 2879
});