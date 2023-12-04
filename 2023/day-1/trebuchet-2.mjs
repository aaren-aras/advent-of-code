import fs from 'fs'; 

fs.readFile('trebuchet.txt', 'utf8', (err, data) => { 
  if (err) {
    console.error(err);
    return;
  }

  const lines = data.split('\n'); 
  const calibSum = lines.reduce((acc, cur) => {
    let calibStr = cur.replace(/one|two|three|four|five|six|seven|eight|nine|\D/g, (match) => {
      switch (match) {
        case 'one':
          return '1';
        case 'two':
          return '2';
        case 'three':
          return '3';
        case 'four':
          return '4';
        case 'five':
          return '5';
        case 'six':
          return '6';
        case 'seven':
          return '7';
        case 'eight':
          return '8';
        case 'nine':
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
  // console.log(calibSum);
});