import com.mongodb.MongoClient;
import com.mongodb.MongoClientURI;
import com.mongodb.MongoException;
import com.mongodb.client.AggregateIterable;
import com.mongodb.client.FindIterable;
import com.mongodb.client.MongoCollection;
import com.mongodb.client.MongoDatabase;
import com.mongodb.client.MongoCursor;
import com.mongodb.client.model.Projections;
import org.bson.*;
import org.bson.conversions.Bson;

public class Main{
  
  public static final String STRING_URI="";
  public static final String DB_NAME="";
  public static final String COLLECTION_NAME="";
  public static final String QUERY="":
  public static final String KEY="";
  
  public static void main(String[] args){
    
    MongoClientURI mongoClientURI = new MongoClientURI(STRING_URI);
    MongoClient mongoClient = new MongoClient(mongoClientURI);
    MongoDatabase database = mongoClient.getDatabase(DB_NAME);
    
    MongoCollection<Document> coll = database.getCollection(COLLECTION_NAME);
    MongoCursor<Document> cursor = coll.find(BsonDocument.parse(QUERY)).projection(Projections.include("KEY")).cursor();
    
    while(cursor.hasNext()){
      Document document = b.next();
      System.out.println(document.getString("KEY"));
    }
    
    // 커서이용시 findIterable 과 aggregateIterable을 같은 코드로 처리할 수 있다.
  }
