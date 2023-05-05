from django.shortcuts import render
from .models import StudentCR

# Create your views here.

def index(request):
    crs = StudentCR.objects.all()
    context = {
        'crs': crs,
    }
    return render(request, 'index.html', context)
