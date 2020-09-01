# Initial Setup

Create a new [GitHub](https://github.com/) repository and name it `data-structures`
All of your work for this class should be kept in this (well-organized!) repository.

You'll need an AWS account to use for your work this semester. [Be careful to avoid unexpected charges](https://docs.aws.amazon.com/awsaccountbilling/latest/aboutv2/checklistforunwantedcharges.html). You will create a Cloud 9 environment in this AWS account for your work in this course. Do not use the Major Studio AWS account that Daniel sent you. You will incur some expenses on AWS but they are very unlikely to exceed what you get on the free tier plus the $100 credit you receive from signing up for [AWS Educate](https://aws.amazon.com/education/awseducate/).

# Weekly Assignment 1

## Part One

1. Using Node.js (in Cloud 9), make a request for each of the ten "Meeting List Agenda" pages for Manhattan. **Important: show the code for all ten requests.** Consider alternatives to copy/pasting the same code 10 times though. Which kind of [looping structure](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Guide/Loops_and_iteration) would be appropriate for this? How can you construct the correct URL and local file path for each request?
```
https://parsons.nyc/aa/m01.html
https://parsons.nyc/aa/m02.html
https://parsons.nyc/aa/m03.html
https://parsons.nyc/aa/m04.html
https://parsons.nyc/aa/m05.html
https://parsons.nyc/aa/m06.html
https://parsons.nyc/aa/m07.html
https://parsons.nyc/aa/m08.html
https://parsons.nyc/aa/m09.html
https://parsons.nyc/aa/m10.html
```

2. Using Node.js: For each of the ten files you requested, save the body as a **text file** to your "local" environment (in AWS Cloud9).

3. Study the HTML structure and tags and begin to think about how you might parse these files to extract relevant data for these AA meetings.

4. Update your GitHub repository with the relevant files: your `js` file and ten `txt` files, plus a `md` file with your documentation. In Canvas, submit the URL of the specific location of this work within your `data-structures` GitHub repository.

## Starter code

Start by installing the `simple-get` npm module (for making HTTP requests) and creating a `data` subdirectory to save your output into:
```console
npm install simple-get
mkdir data
```

Next, create a file called `fetch.js` file with the contents:
```javascript
"use strict"
var get = require('simple-get');
var fs = require('fs');

get.concat('https://parsons.nyc/thesis-2020/', function(error, response, body){
    if (!error && response.statusCode == 200) {
        fs.writeFileSync(`${__dirname}/data/thesis.txt`, body);
    }else{
        console.log(`GET request failed: ${response.statusCode} "${response.statusMessage}"`)
    }
});
```

You can then run it by typing:
```console
node fetch.js
```

#### Documentation:

* [What is `npm`?](https://docs.npmjs.com/getting-started/what-is-npm)
* [Node simple-get module](https://www.npmjs.com/package/simple-get)
* [Node fs module](https://nodejs.org/api/fs.html)
* [Template strings](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Template_literals)

## Map of AA zones

![](https://github.com/samizdatco/ds-2020/raw/master/assets/aa.png)
