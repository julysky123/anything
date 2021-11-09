//elastic.dto.entity에 작성.

package com.example.test.elastic.dto.entity;

import lombok.Getter;
import lombok.Setter;
import org.springframework.boot.context.properties.ConfigurationProperties;
import org.springframework.stereotype.Component;

@Component
@Setter
@Getter
@ConfigurationProperties(prefix = "elasticsearch")
public class ElasticsearchProperties {

    private String host;

    private String username;

    private String password;

}
