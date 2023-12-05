import fs from 'fs'; 

fs.readFile('trebuchet.txt', 'utf8', (err, data) => { 
  if (err) {
    console.error(err);
    return;
  }

  const lines = data.split('\n'); 
  const calibSum = lines.reduce((acc, cur) => {
    // Hint: e.g., 'eighthree' => '83', not '8' (https://tinyurl.com/muzza5z5)
    let calibStr = cur.replace(/one|two|three|four|five|six|seven|eight|nine|\D/g, (match) => {
      switch (match) {
        case 'one':
          if (cur.includes('oneight')) return '18'; 
          return '1';
        case 'two':
          if (cur.includes('twone')) return '21'; 
          return '2';
        case 'three':
          if (cur.includes('threeight')) return '38'; 
          return '3';
        case 'four':
          return '4';
        case 'five':
          if (cur.includes('fiveight')) return '58'; 
          return '5';
        case 'six':
          return '6';
        case 'seven':
          if (cur.includes('sevenine')) return '79'; 
          return '7';
        case 'eight':
          if (cur.includes('eightwo')) return '82'; 
          if (cur.includes('eighthree')) return '83'; 
          return '8';
        case 'nine':
          if (cur.includes('nineight')) return '98'; 
          return '9';
        default:
          return '';
      }
    });
    // console.log(calibStr);
    let calibVal; 

    if (calibStr.length > 2) {
      let firstDigit = calibStr[0];
      let secondDigit = calibStr[calibStr.length - 1];
      calibVal = Number(firstDigit + secondDigit); 
    } else if (calibStr.length === 1) calibVal = Number(calibStr + calibStr);
    else calibVal = Number(calibStr);
    // console.log(calibVal);
    return acc + calibVal;
  }, 0);
  console.log(calibSum); // Output: 55652
});