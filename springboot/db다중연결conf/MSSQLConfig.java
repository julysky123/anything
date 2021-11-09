package com.example.test.config;

import lombok.RequiredArgsConstructor;
import org.springframework.context.annotation.Configuration;
import org.springframework.data.jpa.repository.config.EnableJpaRepositories;

@Configuration
@RequiredArgsConstructor
@EnableJpaRepositories(basePackages = "com.example.test.mssql")
public class MSSQLConfig {
}
