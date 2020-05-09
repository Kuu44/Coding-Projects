#include"field.h"
//public
    field::field()
    {
        imLen=1367;
        imWid=937;
        set();
        FieldS.scale(float(4.65)/imLen,float(3)/imWid);//--(4) | (3)
        FieldS.setOrigin(imLen/2,imWid/2);
        FieldS.setPosition(Vector2f(FieldCenter));
        FieldS.scale(fieldScale,fieldScale);
    }

    void field::draw(RenderTarget* tar){
        tar->draw(FieldS);
    }

    void field::set(){
        if(!FieldT.loadFromFile("img\\field1.jpg"))
            cout<<"err loading texture";
        FieldS.setTexture(FieldT);
    }

