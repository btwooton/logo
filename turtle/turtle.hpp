#ifndef TURTLE_H_
#define TURTLE_H_


#ifndef PI
#define PI 3.14159265
#endif

class Turtle {

    public:

        Turtle(double x, double y, int heading, bool pd);

        double get_x() const;
        double get_y() const;
        double get_heading() const;
        bool isdown() const;

        void set_x(double x);
        void set_y(double y);
        void set_heading(int heading);
        void forward(double amt);
        void backward(double amt);
        void right(int amt);
        void left(int amt);
        void penup();
        void pendown();

    private:

        double x;
        double y;
        int heading;
        bool pd;
};

#endif
