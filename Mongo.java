package service;

import com.mongodb.MongoClient;
import com.mongodb.MongoClientURI;
import com.mongodb.MongoException;
import com.mongodb.client.AggregateIterable;
import com.mongodb.client.FindIterable;
import com.mongodb.client.MongoCollection;
import com.mongodb.client.MongoDatabase;
import org.bson.*;
import org.bson.conversions.Bson;

import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

/********
Author : 곽민종
Description : 몽고DB 연결용 class, 다른 쿼리 필요시 계속 업데이트 하겠음.
CreatedAt : 2021-04-06
UpdatedAt : 2021-04-06
*********/

public class Mongo {

    private MongoClientURI mongoClientURI;
    private MongoClient mongoClient;

    /*******
    Author : 곽민종
    Description : constructor
    CreatedAt : 2021-04-06
    UpdatedAt : 2021-04-06
    *******/
    public Mongo(String stringURI){
        mongoClientURI=new MongoClientURI(stringURI);
        mongoClient = new MongoClient(mongoClientURI);
    }

    /*******
    Author : 곽민종
    Description : 몽고DB aggregate w/ List<Bson>
    CreatedAt : 2021-04-06
    UpdatedAt : 2021-04-06
    *******/
    public AggregateIterable<Document> aggregate(String dbName, String collectionName, List<Bson> pipeline){
        try {
            MongoDatabase database = mongoClient.getDatabase(dbName);
            MongoCollection<Document> coll = database.getCollection(collectionName);
            return coll.aggregate(pipeline);
        }catch(Exception e){
            System.out.println(e.getStackTrace());
            return null;
        }
    }

    /*******
    Author : 곽민종
    Description : 몽고DB aggregate w/ String[]
    CreatedAt : 2021-04-06
    UpdatedAt : 2021-04-06
    *******/
    public AggregateIterable<Document> aggregate(String dbName, String collectionName, String[] bsonArray){
        try {
            List<Bson> pipeline = new ArrayList<>();
            for (String bson : bsonArray) pipeline.add(Document.parse(bson));
            return aggregate(dbName,collectionName,pipeline);
        }catch(Exception e){
            System.out.println(e.getStackTrace());
            return null;
        }
    }

    /*******
    Author : 곽민종
    Description : 몽고DB aggregate w/ String
    CreatedAt : 2021-04-06
    UpdatedAt : 2021-04-06
    *******/
    public AggregateIterable<Document> aggregate(String dbName, String collectionName, String bsonArray){
        try {
            List<Bson> pipeline = BsonArray.parse(bsonArray).getValues().stream()
                                        .map(bsonValue -> (BsonDocument)bsonValue).collect(Collectors.toList());
            return  aggregate(dbName,collectionName,pipeline);
        }catch(Exception e){
            System.out.println(e.getStackTrace());
            return null;
        }
    }

    /*******
    Author : 곽민종
    Description : 몽고DB find w/ BsonDocument
    CreatedAt : 2021-04-06
    UpdatedAt : 2021-04-06
    *******/
    public FindIterable<Document> find(String dbName, String collectionName, BsonDocument bson){
        try {
            MongoDatabase database = mongoClient.getDatabase(dbName);
            MongoCollection<Document> coll = database.getCollection(collectionName);
            return coll.find(bson);
        }catch(Exception e){
            System.out.println(e.getStackTrace());
            return null;
        }
    }

    /*******
    Author : 곽민종
    Description : 몽고DB find w/ String
    CreatedAt : 2021-04-06
    UpdatedAt : 2021-04-06
    *******/
    public FindIterable<Document> find(String dbName, String collectionName, String bson){
        try {
            return find(dbName, collectionName,BsonDocument.parse(bson));
        }catch(Exception e){
            System.out.println(e.getStackTrace());
            return null;
        }
    }
}

