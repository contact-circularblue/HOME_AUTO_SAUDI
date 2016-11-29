bool monitor_client()
{
 if (client.monitor())
  {

Serial.print("Full message=");
Serial.println(rcvd_msg_full);

    //    Serial.println("MONITOR");
    //    lastreply = millis();
    if (RID != "")
    {
      Serial.print("RID= ");
      Serial.println(RID);


//      Serial.print("Rname= ");
//      Serial.println(Rname);

      //    Serial.print("Rcontent= ");
      //    Serial.println(Rcontent);

      ARD_JSON(Rcontent);
      if (success_val == "true")
      {
//        Serial.println("success=TRUE");
        return true;
      }
      else
      {
//        Serial.println("success=FALSE");
        return false;
      }
    }
    else
    {
      return false;
    }
  

  }
}
