from django.db import models

# Create your models here.

class StudentCR(models.Model):
    student_nominated = models.CharField(max_length=100)
    section = models.CharField(max_length=1)
    def __str__(self):
        return self.student_nominated

class Choice(models.Model):
    cr = models.ForeignKey(StudentCR, on_delete=models.CASCADE)
    vote = models.BooleanField()
    def __str__(self):
        return self.cr.student_nominated

