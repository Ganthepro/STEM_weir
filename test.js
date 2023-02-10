
for (let i=0; i<10; i++) {
    task(i);
 }
   
 function task(i) {
   setTimeout(function() {
       console.log(i);
   }, 1000 * i);
 }