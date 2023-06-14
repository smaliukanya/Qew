//Image quest;
//quest.loadFromFile("images/missionbg.jpg");
//quest.createMaskFromColor(Color(0, 0, 0));
//Texture quest_texture;
//quest_texture.loadFromImage(quest);
//Sprite s_quest;
//s_quest.setTexture(quest_texture);
//s_quest.setTextureRect(IntRect(0, 0, 340, 510));
//s_quest.setScale(0.6f, 0.6f);


int getCurrentMission(int x) 
{
	int mission = 0;
	if ((x > 0) && (x < 400)) { mission = 0; }
	if (x > 400) { mission = 1; }
	if (x > 700) { mission = 2; }
	if (x > 2200) { mission = 3; }

	return mission;
}


std::string getTextMission(int currentMission) {
	std::string missionText = "";
	switch (currentMission)
	{
	case 0: {missionText = " Инструкция \n A - влево \n D - вправо \n S - вниз \n W - прыжок"; break; }
	case 1: {missionText = " dlkfkdjfg"; break; }
	case 2: {missionText = "3. lfdkgodfg"; break;}
	case 3: { missionText = " 4. qqqqqq"; break; }
	}

	return missionText;
}