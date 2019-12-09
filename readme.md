gapcheck(){
	if(frontLineTrack != onLine)
	{
		while(backLineTrack == onLine)
		{
			if(frontLineTrack == onLine){
				return true;
			}
			delay(10 milli);
		}
		return false;
	}
}
			