
void init_game();
void finish_game();
void draw_game();
void update_game(float time, int k_up, int k_down, int k_right, int k_left, int k_fire);
int try_to_damage_player(float x, float y, int dmg);
int player_bonuses(float x, float y, int type);
void add_score(int s);

