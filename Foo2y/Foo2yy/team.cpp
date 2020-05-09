#include"team.h"
team::team(string naam, int s) :name(naam), side(s), ch_aktv_flag(1),ALPHA_ON(false)
{
	side = (side >= 0) ? 1 : -1;
	kolor=(side == 1) ? Color(255, 0, 0, 100) : Color(0, 0, 255, 100);
	for (int i = 0; i < TeamSize; i++) {
		//passSpeed=25.0f;
		formationToSet = 2;
		players[i].setName(string(1, 'A' + i));
		players[i].setNum(i + 1);
		players[i].setIcolor(kolor);
		players[i].set_ALPHA_MODE(false);
        players[i].setPosition(formationsDef[formationToSet][i]);
		players[i].set_alpha_pos(formationsDef[formationToSet][i].x, formationsDef[formationToSet][i].y);
	}
	aktv = 0;
}

int  team::check(ball* football)
{
	int to_return = 0;
	for (int i = 0; i < TeamSize; i++) {
		int jhanda = football->withBall(players + i, side);
		if (jhanda == 7)
			to_return = 7;
		else if (jhanda == 1){
            aktv=i;
			to_return = 1;
		}
	}
	return to_return;
}
void team::draw(RenderWindow* tar) {
	for (int i = 0; i < TeamSize; i++)
		players[i].draw(tar);
}
string team::get_aktv(){
    return players[aktv].getNum();
}
Color team::getColor(){
        return kolor;
}
void team::giveInput(Keyboard::Key left, Keyboard::Key right, Keyboard::Key up, Keyboard::Key down, Keyboard::Key changeKey, Keyboard::Key passKey, team* an_team, ball* football, float deltaTime, team* T)
{
	Vector2f input(0, 0);
	for (int i = 0; i < TeamSize; i++) {
		if (i != aktv) players[i].set_directions(und);
	}
	if (Keyboard::isKeyPressed(left)) {
		input.x = -1;
		players[aktv].set_directions(dayan);
	}
	if (Keyboard::isKeyPressed(right)) {
		input.x = 1;
		players[aktv].set_directions(bayan);
	}
	if (Keyboard::isKeyPressed(up)) {
		input.y = -1;
		players[aktv].set_directions(mathi);
	}
	if (Keyboard::isKeyPressed(down)) {
		input.y = 1;
		players[aktv].set_directions(muni);
	}
	if (Keyboard::isKeyPressed(passKey)) {
		players[aktv].setFlag(!(players[aktv].getFlag(pass)), pass);
		Vector2f direction = football->getPosInWin() - players[aktv].get_posInWin();
	}

	//Attack Mode
	for (int i = 0; i < TeamSize; i++)
	{
		if (i == aktv) {
			players[i].set_ALPHA_MODE(false);
		}
		else
		{
			players[i].set_ALPHA_MODE(ALPHA_ON);
		}
	}
	if (football->getCurrentSide() == (side + 1))//CurrentTeam(side+1))
	{
		int n1 = 0, n2 = 0;
		float distances[TeamSize];
		for (int i = 0; i < TeamSize; i++)
		{
			for (int j = 0; j < TeamSize; j++) {
				distances[j] = magnitude(players[i].getFieldPosition() - T->players[j].getFieldPosition());
			}

			for (int j = 0; j < TeamSize; j++)
			{
				if (distances[n1] > distances[j]) n1 = j;
			}
			for (int j = 0; j < TeamSize; j++)
			{
				if (j == n1) break;
				if (distances[n2] > distances[j]) n2 = j;
			}

			sf::Vector2f newTargetPosition, v1, v2;

			v1 = T->players[n1].getFieldPosition() - football->getFieldPosition();
			v2 = T->players[n2].getFieldPosition() - football->getFieldPosition();

			newTargetPosition = football->getFieldPosition() + v1 + v2;

			if (newTargetPosition.x > 0.8f && newTargetPosition.x < 1.0f) newTargetPosition.x = 0.8f;
			if (newTargetPosition.x < -0.8f && newTargetPosition.x > -1.0f) newTargetPosition.x = -0.8f;

			if (newTargetPosition.y > 0.9f && newTargetPosition.y < 1.0f) newTargetPosition.y = 0.9f;
			if (newTargetPosition.y < -0.9f && newTargetPosition.y > -1.0f) newTargetPosition.y = -0.9f;


			if (playerType[formationToSet][i] == 2)
			{
				players[i].set_alpha_pos((side * 0.1 * -1), players[i].getFieldPosition().y); //cout << "Side: " << side << " Defender: P" << i <<endl;
			}
			else if (playerType[formationToSet][i] == 3)
			{
				players[i].set_alpha_pos((formationsDef[formationToSet][i]).x, (formationsDef[formationToSet][i]).y); //cout << "Side: " << side << " GK: P" << i << endl;
			}
			else
			{
				players[i].set_alpha_pos(newTargetPosition.x, newTargetPosition.y); //cout << "Attacker: " << i << endl;
			}
			//cout << "AttackerSide: "<<side<<"Current P:" << i << "Pos: (" << players[i].getFieldPosition().x << " , " << players[i].getFieldPosition().y <<")"<< endl;
		}
		//system("pause");
	}

	//Defensive mode
	else {
		for (int i = 0; i < TeamSize; i++) {
			float range = 0.1f;
			if (
				(football->getFieldPosition().x < (players[i].getFieldPosition().x + range)
					&& football->getFieldPosition().x >(players[i].getFieldPosition().x - range))
				&& (football->getFieldPosition().y<(players[i].getFieldPosition().y + range)
					&& football->getFieldPosition().y >(players[i].getFieldPosition().y - range))
				&&
				(
				(players[i].getFieldPosition().x < (formationsDef[formationToSet][i].x + (range * 3))
					&& players[i].getFieldPosition().x >(formationsDef[formationToSet][i].x - (range * 3)))
					&& (players[i].getFieldPosition().y<(formationsDef[formationToSet][i].y + (range * 3))
						&& players[i].getFieldPosition().y >(formationsDef[formationToSet][i].y - (range * 3)))
					))
			{
				players[i].set_alpha_pos(football->getFieldPosition().x, football->getFieldPosition().y);
			}
			else
			{
				players[i].set_alpha_pos(formationsDef[formationToSet][i].x, formationsDef[formationToSet][i].y);
			}
			if (playerType[formationToSet][i] == 3)
			{
				if (players[i].getFieldPosition().y > 0.2f)
					players[i].set_alpha_pos((formationsDef[formationToSet][i].x), -0.21f);
				else if (players[i].getFieldPosition().y < -0.2f)
					players[i].set_alpha_pos((formationsDef[formationToSet][i].x), 0.21f);
				else
					players[i].set_alpha_pos((formationsDef[formationToSet][i].x), -0.21f); //cout << "Side: " << side << " GK: P" << i << endl;
			}
		}
	}

	if (Keyboard::isKeyPressed(changeKey)) {
		if (ch_aktv_flag) {
			inc_aktv(football);
			ch_aktv_flag = 0;
		}
	}
	else {
		ch_aktv_flag = 1;
	}
	for (int i = 0; i < TeamSize; i++) {
		int tmp = 0;
		if (i == aktv)
			tmp = 1;
		players[i].incSpeed(input * (deltaTime * tmp));
	}
	move(deltaTime, deltaTime, an_team, football);
}
void team::inc_aktv(ball* football) {
	bool no_chatak = false;
	sf::Vector2f tmp=*football-players[aktv];
	if (magnitude(players[aktv].getSpeed()) != 0){
        tmp = players[aktv].getSpeed();
	}
    if(magnitude(tmp)!=0)
    {
        tmp=makeUnitVector(tmp);
		int target_pl = -1;
		float tmp_cmpr = -1;
		for (int i = 0; i < TeamSize; i++) {
			if (i == aktv)
				continue;
			sf::Vector2f rel_vec = makeUnitVector(players[i] - players[aktv]);
			float tmp2_cmpr = getAngle(rel_vec, tmp);
			if (tmp2_cmpr >= 0 && (tmp2_cmpr < tmp_cmpr || tmp_cmpr < 0)) {
				target_pl = i;
				tmp_cmpr = tmp2_cmpr;
			}
		}
		if (tmp_cmpr > 3.1416 / 6 || tmp_cmpr < 0)
			no_chatak = true;
		else {
			aktv = target_pl;
		}
	}
	else if(magnitude(tmp)!=0){}
    else { no_chatak = true; }
	if (no_chatak)
		aktv = (aktv < TeamSize - 1) ? aktv + 1 : aktv;
}
void team::move(float x, float y, team* an_team, ball* football) {
	for (int i = 0; i < TeamSize; i++) {
		if (noCollisionAfter(x, y, an_team, i)) {
			players[i].setPosition();
		}
	}
}
void team::reconfig(){
    for(int i=0;i<TeamSize;i++){
        players[i].setPosition(formationsDef[formationToSet][i]);
        players[i].setSpeed(0,0);
    }
}
void team::set_name(string naam)
{
	name = naam;
}
void team::update() {
	for (int i = 0; i < TeamSize; i++) {
		players[i].incPosition();
	}
}

//Private Functions
float team::dot(sf::Vector2f v1, sf::Vector2f v2)
{
	return (v1.x * v2.x + v1.y * v2.y);
}
float team::getAngle(sf::Vector2f v1,sf::Vector2f v2)
{
	return acos(dot(v1,v2));
}
sf::Vector2f team::makeUnitVector(Vector2f v)
{
	float mag = magnitude(v);
	return Vector2f(v.x / mag, v.y / mag);
}
float team::magnitude(sf::Vector2f v)
{
	return sqrt((v.x * v.x) + (v.y * v.y));
}
int team::noCollisionAfter(float x, float y, team* an_team, int this_pl_N = -1) {
	if (!(this_pl_N >= 0 && this_pl_N < TeamSize))
		this_pl_N = aktv;
	int i = 0;
	int j = 0;
	player* P[2] = { players,an_team->players };
	players[this_pl_N].incPosition(x, y, 1); //1 for affecting v_*** variables only >< default value is 0
	while (i < TeamSize)
	{
		if (j == 0 && i == this_pl_N)
		{
			i++;
			continue;
		}
		P[j][i].incPosition(0, 0); //this must always be called before wCollide to initialise the v_*** variables of required player to the desired value
		if (wCollide(players[this_pl_N], P[j][i])) {
			return 0;
		}
		i++;
		if (j == 0 && i == TeamSize)
		{
			i = 0;
			j++;
		}
	}
	return 1;
}
int team::wCollide(player& a, player& b) {
	sf::Vector2f just = a - b;
	sf::Vector2f tmp(0, 0);
	sf::Vector2f tmpVel_a = a.getSpeed();
	float pS = playerSize * fieldScale;
	if (just.x <= 2 * pS && just.x >= -2 * pS) {                   //Ignore-->//If we replace either of the ps in this line with playerSize, we get an exception
		if (just.y <= 2 * pS && just.y >= -2 * pS) {
			if (just.x > 0)
				tmp.x = (tmpVel_a.x < 0) ? 0 : tmpVel_a.x;
			else if (just.x < 0)
				tmp.x = (tmpVel_a.x > 0) ? 0 : tmpVel_a.x;
			if (just.y > 0)
				tmp.y = (tmpVel_a.y < 0) ? 0 : tmpVel_a.y;
			else if (just.y < 0)
				tmp.y = (tmpVel_a.y > 0) ? 0 : tmpVel_a.y;
			a.setSpeed(tmp);
			//cout<<just.x<<"\t"<<tmp.x<<" , "<<a.getSpeed().y<<"\n";
			return 1;
		}
	}
	return 0;
}

