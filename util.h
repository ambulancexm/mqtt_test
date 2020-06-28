//TODO
//revoir la convertion string char* j'ai loupé un truc
void convertStrChar(String origin, char* convert){
    strcpy(convert,"");
  for(int i=0; i< origin.length(); i++){
    // strcat(convert,origin.charAt(i));
    convert[i] = origin.charAt(i);
  }
  strcat(convert,"\0");
}

char* charToFloat(float origin){
    char buffer[50];
    sprintf(buffer, "%f", origin);
    return buffer;
}