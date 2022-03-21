import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.mongodb.core.MongoTemplate;
import org.springframework.data.mongodb.core.aggregation.*;
import org.springframework.data.mongodb.core.query.Criteria;

import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class DataRepositoryImpl implements CustomDataRepository{

    @Autowired
    private MongoTemplate mongoTemplate;

    @Override
    public Map<Data, Integer> getDataCount(LocalDate st, LocalDate ed) {

        DateTimeFormatter dateTimeFormatter = DateTimeFormatter.ofPattern("yyyy-MM-dd");
        String stDate = st.format(dateTimeFormatter);
        String edDate = ed.format(dateTimeFormatter);

        MatchOperation matchStage = Aggregation.match(new Criteria("create_date").gte(stDate).lt(edDate));
        GroupOperation groupStage = Aggregation.group("key1","key2","key3").count().as("count");
        Aggregation aggregation = Aggregation.newAggregation(matchStage, groupStage);

        AggregationResults<HashMap> aggregationResults = mongoTemplate.aggregate(aggregation,"COLLECTION", HashMap.class);



        List<HashMap> list = aggregationResults.getMappedResults();
        Map<Data, Integer>  result = new HashMap<>();

        for(HashMap hashMap: list){
            HashMap<String,String> idMap = (HashMap<String, String>) hashMap.get("_id");

            DataCount DataCount = DataCount.builder()
                    .key1(idMap.get("key1"))
                    .key2(idMap.get("key2"))
                    .key3(idMap.get("key3"))
                    .key4(null)
                    .count((Integer)hashMap.get("count"))
                    .build();
            System.out.println(DataCount.toString());
            result.put(Data.of(DataCount), DataCount.getCount());
        }

        return result;
    }
}
