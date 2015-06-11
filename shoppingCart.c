/*
  Name: Shopping Cart
  Author: Grayce Stalowski
  Date: 03/08/14 16:15
  Description: This is a program to create a shopping cart that will:
               1. Let users add items and prices to the cart
               2. Let users calculate and see the sales tax
               3. Let users calculate and see the s&h
               4. Let users calculate and see the total bill
               5. Let users checkout- Just says you owe $x press key to checkout
               6. Let users save cart to a file for later access
Commented out code is for debugging purposes
Goes with cart.txt file
*/
#include <stdio.h>
#include <ctype.h> //to use isdigit
#include <stdlib.h> //to use atoi and atof to convert string to int or double

//This is a 2 dimentional array, 1 is for 10 letters in each array of chaacters
//2 is for 10 items total so it stores 10 arrays each of 10 characters
char items[25][10]={0};

//use float over double here because it is in an array and floats use less memory
//float is less precise but for money we only need 2 decimal places so it is good
float prices[10]; //just a float so single dimensioin array

//keeps track of what spot in array we are on for storing the items
int counter=0;
float sum;
int end =1;  //exits asking for menu choice when this is 0 
char c='c'; //stores character if user enters only 1 character 
char priceSave[10][10];
int err=0; //switch to 1 if error so menu runs again
 
int enterItems(); 
int printCart();
float salesTax();
float shipping();
float getSum();
int checkout();
int saveCart();
int openCart();


int main (void)
{
 char choice[10]="c"; //stores string of what user enters
 char c='c'; //stores character if user enterss only 1 character
 int intC=1; // converts choice into an int to check if it is the right range
  
  
 printf("Welcome to Grayce's Store!\n"); //above while loop so it only runs once
    
 //while loop to get and check input
 //This condition should probably be changed to or || but can be tested later
//two while loops are needed. 1 to check if the end condition is 1 or 0
//One to check if the input is correct

 while( !(isdigit(c)))
 {   
  //User interface menu
  printf("\nWhat would you like to do?\n");
  printf("\n1: Add item to cart\n");
  printf("2: View current cart\n");
  printf("3: Calculate sales tax\n");
  printf("4: Calculate shipping and handling\n");
  printf("5: Checkout\n");
  printf("6: Save cart for later\n");
  printf("7: Open cart previously saved\n");
  printf("8: Exit\n");            
  
  printf("Enter choice: ");
  scanf("%s",&choice);
  //printf("\nYou chose: %s\n",choice);  
  
  //if only 1 character convert to c
  if(strlen(choice)==1)
  {
   c=choice[0];
   // printf("success\n");                
  }
  
  //check if c is a number
  //if choice wasn't one character it will keep c at 'c' as it is initially so else runs here
  if ( isdigit(c)){
   //printf("It is a number!\n");
   //printf("\nYou chose: %s\n",choice);
   intC= atoi(choice);                       
  }
  else{
   printf("\nPlease enter a number!\n");     
  }
  
  //if range is invalid ask for valid number
  if(intC<1||intC>8){
   //printf("%d\n",intC);                
   printf("Please enter a valid numer!\n");
   c='c'; //make c a character so the loop runs again to ask for input       
  }

 //now we have the user's choice stored as a string, a character, and an int!
 //All three types were necessary to check for errors in the input 
 
  if(isdigit(c)){
   switch(intC){
      case 1:
            enterItem();
            c='c'; //set c to be a character so the loop runs again
            break;
      case 2:
            printCart();
            c='c';
            break;
      case 3:
            salesTax();
            c='c';
            break;
      case 4:
            shipping();
            c='c';
            break;
      case 5:
            checkout();
            if(err==0){ //if no error end
             end=0;
            }
            else{ //else (error) set c so menu runs again
             c='c';
            }
            break;
      case 6:
            saveCart();
            if(err==1){ //if error set c so menu runs again
             c='c';           
            }
            break;
      case 7:
            openCart();
            c='c';
            break;
      case 8:
           exit(0);
           break;      
      default:
              printf("default\n");
              break;                                     
   }//end case
  }//end if
 }//end while loop
 
 getch();
 return 0;
}//end main

//enterItem function
enterItem(){
 char item[10];
 float price; 
 char priceEntered[10];
 int isDigit=1;
 
 printf("\nEnter item name: ");
 //don't bother checking just save name as string
 scanf("%s",&item);

 while(isDigit!=0)
 {
  isDigit=0; //set it to 0 so it doesn't run again if all input is good
  printf("\nEnter item price: $");
  //scanf("%f",&price);
  //should check that it is a double but it's complex
  scanf("%s",&priceEntered);
 
  int n=0;//counter
  /*For loop to go through each position in the chaacter array that the price is stored in
  It checks if each character is a digit or is a decimal point
  If it is not a digit isDigit gets set to 1 and then it reasks for input.*/
  for(n=0;n<strlen(priceEntered);n++){
   if(isdigit(priceEntered[n])||priceEntered[n]=='.'){ 
    //do nothing                         
   } //end if
   else{
    isDigit=1;    
    //printf("no\n");     
   }//end else
  }//end for loop
  if(isDigit==1){
   printf("Please enter a valid number\n");               
  }//end if
 }//end while loop
 
 //convert character string to float using atof() function
 price=atof(priceEntered);
 //put price and item name into their respective arrays
 prices[counter]=price;
 strcpy(items[counter],item);
 strcpy(priceSave[counter],priceEntered);
 //print out
 printf("%s for $%.2f has been added to your cart.\n",items[counter],prices[counter]);
 counter++;
 return 0;            
}//end function

//printCart function
printCart(){
 if(items[0][0]==0){
  printf("\nCart is empty\n");                   
 }
 else{         
  int i;             
  printf("\nYour cart: \n");
  printf("   Item \tPrice \n");//put above loop so it only prints once
  for(i=0;i<counter;i++){
   printf("%d: %s  \t$%.2f\n",i+1,items[i],prices[i]);
  }//end for loop
  sum=getSum();
  printf("\nTotal:\t\t$%.2f\n",sum);
 }//end else which only runs if cart is not empty
 return 0;     
}//end function

float salesTax() {
 float taxRate; //rate 
 float taxPay; //amount to be paid
 float taxPercent; //percent to print out onscreen
 int i=0;
 
 if(items[0][0]==0){
  printf("\nAdd items to cart first\n");                   
 }          
 else{
  char taxString[10];//to check that it is valid
  int isDigit=1; //to check if input is valid 
  sum=getSum();

  //while loop to get and validate the tax percent rate 
  while(isDigit!=0)
  {
   isDigit=0; //set it to 0 so it doesn't run again if all input is good
   printf("\nEnter tax percent rate as decimal: ");
   scanf("%s",&taxString);
 
   int n=0;//counter
   /*For loop to go through each position in the chaacter array that the price is stored in
   It checks if each character is a digit.
   If it is not a digit isDigit gets set to 1 and then it reasks for input.*/
   for(n=0;n<strlen(taxString);n++){
    if(isdigit(taxString[n])||taxString[n]=='.'){
     //do nothing                             
    }//end if 
    else{
     isDigit=1;         
    }//end else
   }//end for loop
   if(isDigit==1){
    printf("Please enter a valid number\n");               
   }//end if
 }//end while loop

 //convert character string to float using atof() function
  taxRate=atof(taxString); 
  taxPercent=taxRate*100; //so it can be printed nicelu
  //Calculate and print tax pay
  taxPay=taxRate*sum;
  printf("Tax at %.0f%% is $%.2f\n",taxPercent,taxPay);

  return taxPay;  
 }//end else           
} //end function

//shipping function
float shipping(){
 float shipping;
 if(items[0][0]==0){
  printf("\nAdd items to cart first\n");                   
 }
 else{
  
  printf("\nIf you spend $100+ you get free shipping!\n");
  getSum();
  if(sum>=100){
   shipping=0.00;
   printf("You spent $100+ and get free shipping!");        
  }//end if
  else{
   shipping=5.95;
   printf("Shipping costs are $%.2f\n",shipping);      
  }//end else
 }//end else 
 return shipping;       
}//end function

float getSum(){
 if(items[0][0]==0){
  printf("\nAdd items to cart first.\n");                   
 }
 else{
  int i=0;
  sum=0;
 
  for(i=0;i<counter;i++){
   sum+=prices[i];                   
  }
  //printf("Sum: $%.2f\n",sum);
 }//end else
 return sum;        
}//end function

checkout(){
 err=0;          
 if(items[0][0]==0){
  printf("\nAdd items to cart first\n");
  err=1;                   
 }
 else{
  end=1;
  float tax;
  float shippingCharge;
  float totalItems;
  float totalOwe;

  printCart();

  tax=salesTax();
  shippingCharge=shipping();
  totalItems=getSum();
  totalOwe=tax+shippingCharge+totalItems;

  printf("\nYou owe: $%.2f\n",totalOwe);
  printf("Thanks you for shopping with us!\n");
  printf("Press any key to exit.");
 }//end else
 return 0;           
}//end function

saveCart(){
 err=0;          
 if(items[0][0]==0){
  printf("\nAdd items to cart first\n");
  err=1;                   
 }
 else{
 
  char s=' ';
  char n[4]="\n";          
  FILE *fp = fopen("cart.txt", "w+");
  int i;
  fputs("Your cart: \n",fp);

 //for loop to put items into file
  for(i=0;i<counter;i++){
   fputs(items[i],fp);
   fputc(s,fp); //use putc for 1 character
  }//end for loop
 
  fputs(n,fp);//put a newline in te file
 
  //for loop to put prices into file
  for(i=0;i<counter;i++){
   fputs(priceSave[i],fp);
   fputc(s,fp);
  }//end for loop
 
  fclose(fp);
  printf("Your cart has been saved.\n");
  printf("Press any key to exit");
 }//end else              
 return 0;           
}

openCart(){
 if(items[0][0]!=0){
  printf("\nCart must be opened before other items are added.\n");                   
 }          
 else{          
 FILE *fp = fopen("cart.txt", "r");
 int i=0;
 char buff[25];
 int isDigit;
 float price;
 
 fgets(buff, 25, (FILE*)fp); //get the 1st line which just says your cart
   
 fscanf(fp, "%s", buff);//gets first item in file so the while loop can start
 //put all input that is an item name into the items array 
 isDigit=1;
 while(isDigit!=0){ //white it is not a digit
  isDigit=0; //set it to 0 so it doesn't run again if input is a number
  int n=0;//counter
  /*For loop to go through each position in the chaacter array that the price is stored in
  It checks if each character is a digit.
  If it is not a digit isDigit gets set to 1 and then it reasks for input.*/
  for(n=0;n<strlen(buff);n++){
   if(isdigit(buff[n])||buff[n]=='.'){ //if it is a digit
    //do nothing if it is a digit                             
   } 
   else{ //not digit
   isDigit=1;        
   }
  }//end for loop
  if(isDigit==1){
   strcpy(items[i],buff);
   i++; //increase i which is variable for items index
   fscanf(fp, "%s", buff); 
   counter+=1; //increase counter which is number of items in the items array
  }//end if
  else{
   //do nothing
  }
 }//end while loop for items 

 i=0;//reset i
  
 //put all input that is a number aka a price into the prices array
 isDigit=1;
 while(isDigit!=0){
  isDigit=0; //set it to 0 so it doesn't run again if input is a number
 while (fgetc(fp) != EOF){ //while the next character is not end of file
  int n=0;//counter
  /*For loop to go through each position in the chaacter array that the price is stored in
  It checks if each character is a digit.
  If it is not a digit isDigit gets set to 1 and then it reasks for input.*/
  for(n=0;n<strlen(buff);n++){ 
   if(isdigit(buff[n])||buff[n]=='.'){ //if it is a digit
    isDigit=1;        
   }//end if 
   else{ //not digit
    //do nothing
   }
  }//end for loop
  
  if(isDigit=1){
   //printf("%d: ",i);
   //printf("%s\n", buff );
   price=atof(buff);
   prices[i]=price;
   i++;  
   fscanf(fp, "%s", buff);          
  }//end if
  
 }//end while loop 
}//end second while loop for all input from file
 
 fclose(fp);
 //if the first item in item array is not null print out it is suvccessful, else not
 if( (items[0]!=NULL)  ){
  printf("\nCart loaded successfully.\n");           
 }
 else{
  printf("\nError: Cart not loaded.\n");     
 }
}//end else which checks if items were added else opens cart 
 return 0;           
}//end function
