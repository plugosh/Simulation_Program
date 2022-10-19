pipeline {
    agent any

    stages {
        stage('Checkout') {
            steps {
                checkout([$class: 'GitSCM', branches: [[name: '*/main']], extensions: [], userRemoteConfigs: [[url: 'https://github.com/plugosh/Simulation_Program']]])
            }
        }
        stage('Build') {
            steps {
                sh 'python3 ops.py'
            }
        }
        stage('Test') {
            steps {
                sh 'python3 ops.py check'
            }
        }
        stage('publish') {
            steps {
                sh "chmod a+x 'Publish.sh'"
                sh 'Publish.sh'
            }
        }
    }
}
      
