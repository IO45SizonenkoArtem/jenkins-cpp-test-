pipeline {
    agent any

    stages {
        stage('Checkout') {
            steps {
                // Завантажуємо код з GitHub
                checkout scm
            }
        }

        stage('Build') {
            steps {
                // Збираємо проект
                // Переконайся, що назва інструмента 'VS_Build' збігається з тим, що в Global Tool Configuration
                bat "\"${tool 'VS_Build'}\" test_repos.sln /t:Rebuild /p:Configuration=Debug /p:Platform=x64"
            }
        }

        stage('Test') {
            steps {
                // Запускаємо тести і генеруємо XML-звіт
                bat "x64\\Debug\\test_repos.exe --gtest_output=xml:test_report.xml"
            }
        }
    }

    post {
        always {
            // Публікуємо результати (JUnit плагін є стандартним і надійним)
            junit 'test_report.xml'
        }
    }
}