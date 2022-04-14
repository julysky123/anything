package factory;

import shapes.Circle;
import shapes.IShape;
import shapes.Rectangle;

import java.util.HashMap;
import java.util.Map;

public class ShapeFactory {

    private ShapeFactory(){
        register(1, Circle.class);
        register(2, Rectangle.class);
    };

    private Map<Integer, Class<? extends IShape>> classMap = new HashMap<>();

    private static ShapeFactory instance = new ShapeFactory();
    public static ShapeFactory getInstance(){
        return instance;
    }

    public IShape create(int type) throws IllegalAccessException, InstantiationException {
        IShape p = null;
        if(classMap.containsKey(type)){
            p = classMap.get(type).newInstance();
        }
        return p;
    }

    public void register(int key, Class<? extends IShape> c){
        classMap.put(key,c);
    }
    public void show(){
        System.out.println("-- show all shapes --");
        for(Integer i : classMap.keySet()){
            System.out.println(""+i+": "+classMap.get(i).getName());
        }
    }


}
