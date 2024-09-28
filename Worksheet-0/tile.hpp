class Tile {
    public:
        Tile(int val = 0);
        int getState();
        void setState(int state);
        char getStateStr();
    private:
        int state;
};