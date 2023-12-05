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
          // Handle 'oneightwo', 'oneighthree'?
          if (cur.includes('eight')) return '18'; // Handle 'oneight' 
          return '1';
        case 'two':
          // Handle 'twoneight'?
          if (cur.includes('one')) return '21'; // Handle 'twone'
          return '2';
        case 'three':
          // Handle 'threeightwo', 'threeightwoneighthree', 'threeighthree'?
          if (cur.includes('eight')) return '38'; // Handle 'threeight' 
          return '3';
        case 'four':
          return '4';
        case 'five':
          if (cur.includes('eight')) return '58'; // Handle 'fiveight'
          return '5';
        case 'six':
          return '6';
        case 'seven':
          if (cur.includes('nine')) return '79'; // Handle 'sevenine'
          return '7';
        case 'eight':
          if (cur.includes('two')) return '82'; // Handle 'eightwo'
          if (cur.includes('three')) return '83'; // Handle 'eighthree'
          return '8';
        case 'nine':
          if (cur.includes('eight')) return '98'; // Handle 'nineight'
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
    console.log(calibVal);
    return acc + calibVal;
  }, 0);
  console.log(calibSum);
});