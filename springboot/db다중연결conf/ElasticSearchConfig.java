package //;

import com.example.test.elastic.dto.entity.ElasticsearchProperties;
import org.elasticsearch.client.RestHighLevelClient;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
import org.springframework.data.elasticsearch.client.ClientConfiguration;
import org.springframework.data.elasticsearch.client.RestClients;
import org.springframework.data.elasticsearch.repository.config.EnableElasticsearchRepositories;

@Configuration
@EnableElasticsearchRepositories(basePackages = "com.example.test.elastic.dto.repository")
@ComponentScan(basePackages = { "com.example.test.elastic" })
public class ElasticSearchConfig {

    @Bean
    public RestHighLevelClient client(ElasticsearchProperties properties) {

        ClientConfiguration clientConfiguration = ClientConfiguration.builder()
                .connectedTo(properties.getHost())
                .withBasicAuth(properties.getUsername(), properties.getPassword())
                .build();
        return RestClients.create(clientConfiguration).rest();
    }
}
