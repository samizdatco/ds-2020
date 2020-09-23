# Weekly Assignment 4

### Due 9/29 at 6:00pm

You're going to continue working with the data you scraped, parsed, and augmented in the previous three assignments. In this assignment, you will write your AA data to a relational database. 

## Setup and preparation

You will use Amazon Web Services to host a PostgreSQL database server. Follow the instructions below to set up and access an instance you will use for your SQL work in this class; the setup should take about 30 minutes to complete. 

If you have trouble connecting to your AWS RDS instance, refer to [this guide](https://aws.amazon.com/premiumsupport/knowledge-center/rds-cannot-connect/). 

If you are new to SQL, consider [this tutorial](https://www.linkedin.com/learning/sql-essential-training-2).



#### Creating a PostgreSQL DB Instance in AWS

*These steps only need to be completed once, to set up your instance.* 

1. Use your AWS account credentials to log in to the [AWS Console](https://console.aws.amazon.com/console/home?region=us-east-1).  
2. The console shows a long list of AWS services. Find and click on the **RDS** service.  
3. In the left-hand column, click **Databases**.  
4. Click the orange **Create database** button.  
5. Make the following changes on this page; for the sections/options that aren't mentioned in this instruction, leave the default settings. In the **Choose a database creation method** section, click the **Standard Create** radio button. In the **Engine options** section, click the **PostgreSQL** radio button. In the **Templates** section, click the **Free tier** radio button. In the **Settings** section in the **DB instance identifier** field, enter this name: `data-structures`. In the **Master username** field, enter a username that is easy for you to remember. In the **Master password** and **Confirm password** fields, enter a secure password that is easy for you to remember. **Keep track of your username and password. You'll need them later!** Expand the **Additional configuration** section and in the **Initial database name** field, enter `aa`. Finally, click the orange **Create database** button.   

It will take a few minutes for AWS to create your DB instance. It is available for use when the status is **available**. When it is **available**, complete the following steps to access the instance:

#### Setting up a way to access your instance

*These steps only need to be completed once, to set up access to your instance.* 

1. In RDS > Databases: Click on the url for your instance name to reveal its metadata and options.  
2. Scroll down to the **Security Group Rules** section. Click on the url for the rule that includes the work **Inbound** in its type description. Click the **Inbound rules** tab. Click the **Edit inbound rules** button. Click the **Add Rule** button. In the **Type** dropdown, select **All traffic**. From the **Source** dropdown, select **Anywhere** from the drop-down menu. At the bottom right, click the orange **Save rules** button.  
3. You are now ready to connect to your new database.  

## Assignment

### Part One: Plan

Using the Hills text as a starting point (but feel free to strike out on your own), draw a data model for the AA meetings data to be stored in a database. Include all the content/data/variables from the source file that you believe to be relevant, even if you haven't parsed it yet. Upload an image (`png` format) of your drawing to your GitHub repository.  

Some decisions that will help with this drawing:  
1. Will you use a [Normalized Data Model or a Denormalized Data Model](https://www.quora.com/What-is-normalized-vs-denormalized-data)? Why?  
2. When the data comes back out of the database, how should it be structured? Why?  
3. How would you describe the hierarchy of the data?  

### Part Two: Create a table(s) in your database

Modify the following starter code to replace the database credentials with your own. It includes two SQL sample statements that you can modify to accomplish any of the following tasks in your new database, with the help of the [`pg` module](https://node-postgres.com/) in Node:  

1. Create a new table.  
2. Remove (delete!) a table.  

**`wa04-a-init.js`** 

```javascript
const {Client} = require('pg'),
      dotenv = require('dotenv');


// AWS RDS POSTGRESQL INSTANCE
dotenv.config(); 
let db_credentials = {
    host: 'dsdemo.c2g7qw1juwkg.us-east-1.rds.amazonaws.com',
    database: 'mydb',
    user: 'aaron',
    password: process.env.AWSRDS_PW,
    port: 5432,
}

// Connect to the AWS RDS Postgres database
const client = new Client(db_credentials);
client.connect();

// Sample SQL statement to create a table (using ` quotes to break into multiple lines):
let query = `CREATE TABLE aalocations (
  address varchar(100),
  lat double precision,
  long double precision
);`;

// Sample SQL statement to delete a table:
// let query = "DROP TABLE aalocations;";

client.query(query, (err, res) => {
    if (err){ throw err; }

    console.log(res);
    client.end();
});
```

### Part Three: Populate your database

Use the `pg` module to insert your AA data in the database you created. Hint: check to make sure you have the correct number of rows! **Note: it is not expected that this data be complete and clean yet. For now, just insert the documents/data you have.**  

The following starter code loops over a list of three addresses and creates a [parameterized](https://node-postgres.com/features/queries) SQL query from each in order to add rows to the database. Modify the code to use your authentication credentials and replace the hard-coded `addressesForDb` values with dynamically loaded data from your json files. 

**`wa04-b-populate.js`** 

```javascript
const {Client} = require('pg'),
      dotenv = require('dotenv'),
      async = require('async');

dotenv.config(); 
let db_credentials = {
    host: 'dsdemo.c2g7qw1juwkg.us-east-1.rds.amazonaws.com',
    database: 'mydb',
    user: 'aaron',
    password: process.env.AWSRDS_PW,
    port: 5432,
}

let addressesForDb = [
  {address: '63 Fifth Ave, New York, NY', latLong: {lat: 40.7353041, lng: -73.99413539999999} },
  {address: '16 E 16th St, New York, NY', latLong: {lat: 40.736765,  lng: -73.9919024} },
  {address: '2 W 13th St, New York, NY',  latLong: {lat: 40.7353297, lng: -73.99447889999999} }
];

async.eachSeries(addressesForDb, function(value, callback) {
    let client = new Client(db_credentials);
    client.connect();

    // When mixing variables into a query, place them in a `values` array and then refer to those 
    // elements within the `text` portion of the query using $1, $2, etc.
    let query = {
      text: "INSERT INTO aalocations VALUES($1, $2, $3)",
      values: [value.address, value.latLong.lat, value.latLong.lng]
    };

    client.query(query, (err, res) => {
        if (err){ throw err; }

        console.log(res);
        client.end();
    });
    setTimeout(callback, 1000);
});
```

### Part Four: Check your work

To see what's in your new database table, let's query all of its contents: 

**`wa04-c-report.js`** 

```javascript
const {Client} = require('pg'),
      dotenv = require('dotenv');

dotenv.config(); 
let db_credentials = {
    host: 'dsdemo.c2g7qw1juwkg.us-east-1.rds.amazonaws.com',
    database: 'mydb',
    user: 'aaron',
    password: process.env.AWSRDS_PW,
    port: 5432,
}

// Connect to the AWS RDS Postgres database
const client = new Client(db_credentials);
client.connect();

// Sample SQL statement to query the entire contents of a table: 
let query = "SELECT * FROM aalocations;";

client.query(query, (err, res) => {
    if (err){ throw err; }

    console.log(res.rows);
    client.end();
});
```

### Submission requirements

Update your GitHub repository with the relevant file(s). In Canvas, submit the URL of the specific location of this work within your `data-structures` GitHub repository. 
