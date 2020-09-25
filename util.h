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

char * stringToChar(String str) {
  char tmp[str.length()+1];
  Serial.println("");
  for (int i =0; i< str.length(); i++){
    Serial.print(str[i]);
    tmp[i] = str[i];
    Serial.print(":");
    Serial.println(tmp[i]);

  }

  tmp[str.length()] ='\0';
  Serial.print("str :" );
  Serial.println(tmp);
  return tmp;
}