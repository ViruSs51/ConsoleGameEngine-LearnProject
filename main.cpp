#include <iostream>

using namespace std;

typedef struct
{
    long long width, height;
} TMapSize;

typedef struct
{
    char **place;
} TMatrix;

class Map
{
private:
    TMapSize _size;
    TMatrix matrix;
    char background;

    //Create a matrix width on height with char type and fill this matrix with background's char
    void initPlace()
    {
        char **p = new char* [_size.height];
        for (int row=0; row<_size.height; row++)
        {
            p[row] = new char [_size.width+1];
            for (int col=0; col<_size.width; col++) p[row][col] = background;
            p[row][_size.width] = '\0';
        }
        matrix.place = p;
    }

    void setBorder(int side, char _s='*')
    {
        switch (side)
        {
        case 1:
            for (int x=0; x<_size.width; x++) setPoint(x, 0, _s);
            break;

        case 2:
            for (int y=0; y<_size.height; y++) setPoint(_size.width-1, y, _s);
            break;

        case 3:
            for (int x=0; x<_size.width; x++) setPoint(x, _size.height-1, _s);
            break;

        case 4:
            for (int y=0; y<_size.height; y++) setPoint(0, y, _s);
            break;

        default:
            setBorder(side=1, _s=_s);
            setBorder(side=2, _s=_s);
            setBorder(side=3, _s=_s);
            setBorder(side=4, _s=_s);
            break;
        }
    }

public:
    //Init matrix place
    Map(long long width=10, long long height=10, char _background=' ')
    {
        _size.width = width;
        _size.height = height;
        background = _background;

        initPlace();
    }

    //Border methods
    void setBorder(char symbol='*'){setBorder(0, symbol);} //Set border for place
    void topBorder(char symbol='*'){setBorder(1, symbol);} //Set border top for place
    void leftBorder(char symbol='*'){setBorder(2, symbol);} //Set border left for place
    void bottomBorder(char symbol='*'){setBorder(3, symbol);} //Set border bottom for place
    void rigthBorder(char symbol='*'){setBorder(4, symbol);} //Set border right for place

    //Getter methods
    TMapSize getSize(){return _size;} //Return matrix size
    TMatrix getMatrix() //Return matrix
    {
        TMatrix copy_matrix;
        char **p = new char* [_size.height];

        for (int row=0; row<_size.height; row++)
        {
            p[row] = new char [_size.width+1];
            for (int col=0; col<_size.width+1; col++) p[row][col] = matrix.place[row][col];

        }
        copy_matrix.place = p;

        return copy_matrix;
    }

    void setPoint(int x, int y, char symbol)
    {
        matrix.place[y][x] = symbol;
    }

    //Concatination two matrixes
    bool concat(Map _obj, int axes=1)
    {
        /*
            This method returned execute status, false=error, true=not error.
        */

        TMapSize obj_size = _obj.getSize();
        TMatrix obj_matrix = _obj.getMatrix();
        TMapSize new_size;

        if (axes == 0)
        {
            if (obj_size.width != _size.width) return false;

            new_size.width = _size.width;
            new_size.height = _size.height + obj_size.height;
        }else if (axes == 1)
        {
            if (obj_size.height != _size.height) return false;

            new_size.width = _size.width + obj_size.width;
            new_size.height = _size.height;
        }else return false;

        char **p = new char* [new_size.height];
        for (int row=0; row<new_size.height; row++)
        {
            p[row] = new char [new_size.width+1];

            for (int col=0; col<new_size.width; col++)
            {
                switch (axes)
                {
                case 0:
                    (row < _size.height)? p[row][col] = matrix.place[row][col] : p[row][col] = obj_matrix.place[row-_size.height][col];
                    break;

                case 1:
                    (col < _size.width)? p[row][col] = matrix.place[row][col] : p[row][col] = obj_matrix.place[row][col-_size.width];
                    break;

                default:
                    return false;
                }

            }
            p[row][new_size.width] = '\0';
        }

        del();
        _size = new_size;
        matrix.place = p;

        return true;
    }

    //Delete all map
    void del()
    {
        for (int row=0; row<_size.height; row++) delete [] matrix.place[row];
        delete [] matrix.place;

        matrix.place = nullptr;
    }
};

class Console
{
public:
    void cClear(){system("cls");} //Clear console
    template<class T> void print(T str){cout << str;} //Print on console

    void showMatrix(TMatrix _matrix, TMapSize _size)
    {
        for (int row=0; row<_size.height; row++) cout << _matrix.place[row] << endl;
    }
};

int main()
{
    //Testing

    Map world1(10, 5, ' ');
    Console console;

    world1.setBorder('#');

    //console.cClear();
    console.showMatrix(world1.getMatrix(), world1.getSize());

    world1.del();

    return 0;
}
