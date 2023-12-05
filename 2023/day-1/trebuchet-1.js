// Alternatively, use `const fs = require('fs');` w/ `.js` extension (CommonJS) 
import fs from 'fs'; // Import `fs` module for filesystem operations (https://tinyurl.com/4f3cabtf)

fs.readFile('trebuchet.txt', 'utf8', (err, data) => {
  if (err) {
    console.error(err);
    return;
  }

  const lines = data.split('\n'); // Splits data string into array of substrings
  const calibSum = lines.reduce((acc, cur) => {
    let calibStr = cur.replace(/\D/g, ''); // Use regex to remove non-numeric characters
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
  console.log(calibSum); // Output: 56108
});