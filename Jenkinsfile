pipeline {
    agent any

    stages {
        stage('Checkout') {
            steps {
                checkout scm
            }
        }

        stage('Build') {
            steps {
                // Додано Restore; перед Rebuild для відновлення пакетів NuGet
                bat "\"${tool 'VS_Build'}\" test_repos.sln /t:Restore;Rebuild /p:Configuration=Debug /p:Platform=x64"
            }
        }

        stage('Test') {
            steps {
                bat "x64\\Debug\\test_repos.exe --gtest_output=xml:test_report.xml"
            }
        }
    }

    post {
        always {
            junit 'test_report.xml'
        }
    }
}